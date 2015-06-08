#include <Puzzle.hpp>
#include <resources.hpp>
#include <draw/Drawable.hpp>


const int num_logic_puzzle_statues = 3;
const int logic_correct_statue = 1;

// Adjacent string literals are concatenated by the compiler
const char *logic_puzzle_hints[] = {
    "You read the following words on the statue:\n"
    "The knight's words are always true.\n"
    "The knave's words are always false.\n"
    "The spy's words may be anything.\n"
    "Select the knight and then press F.\n"
    "The selected statue is the one you last interacted with.\n"
    "I say: I am the knight!\n",
    
    "The knight's words are always true.\n"
    "The knave's words are always false.\n"
    "The spy's words may be anything.\n"
    "Select the knight and then press F.\n"
    "The selected statue is the one you last interacted with.\n"
    "I say: I am not the spy!\n",
        
    "The knight's words are always true.\n"
    "The knave's words are always false.\n"
    "The spy's words may be anything.\n"
    "Select the knight and then press F.\n"
    "The selected statue is the one you last interacted with.\n"
    "I say: I am the knave!\n",
};

const Eigen::Vector3f statue_positions[] = {
    Eigen::Vector3f(34.0f, 0.5f, 20.0f),
    Eigen::Vector3f(38.0f, 0.5f, 22.0f),
    Eigen::Vector3f(34.0f, 0.5f, 25.0f),
};

std::shared_ptr<Puzzle> PuzzleFactory::createPuzzle(ColRow top_left,
                                                    ColRow bottom_right,
                                                    const char *config_file) {
    YAML::Node config = YAML::LoadFile(config_file);

    if (!config["puzzle"]) {
        return std::make_shared<Puzzle>();
    }
    YAML::Node pconf = config["puzzle"];
    
    PuzzleConfig puzzle_config;


    puzzle_config.name = pconf["name"].as<std::string>();

    std::string type_string = pconf["type"].as<std::string>();


    if (type_string == "logic") {
        puzzle_config.type = LOGIC;
    }
    else if (type_string == "pattern") {
        puzzle_config.type = PATTERN;
    }
    else if (type_string == "pathing") {
        puzzle_config.type = PATHING;
    }
    else {
        std::cerr << "invalid puzzle type string: " << type_string
                  << "in file " << config_file << std::endl;
        
        std::exit(EXIT_FAILURE);

    }

    LOG("loading statue config");
    ModelConfig model_conf;
    resource::load_config(&model_conf, "resources/statue.yaml");
    LOG("Loaded statue config");

    LOG("creating drawable");
    draw::Drawable *drawable = new draw::Drawable(model_conf);
    LOG("done creating drawable");
    std::shared_ptr<Puzzle> puzzle;
    switch (puzzle_config.type) {
    case LOGIC: {
        std::shared_ptr<LogicPuzzle> puzzle;
        puzzle = std::make_shared<LogicPuzzle>();
        puzzle->setSuccess(false);
        for (int i = 0; i < num_logic_puzzle_statues; i++) {
            Entity *statue = new Entity(drawable);
            statue->setPosition(statue_positions[i]);
            LOG("puzzle statue id: " << statue->id);
            puzzle->entities.push_back(statue);
        }
        puzzle->correct_entity = puzzle->entities[logic_correct_statue];
        
        return puzzle;
    }
    case PATTERN: {
        std::shared_ptr<PatternPuzzle> puzzle;
        puzzle = std::make_shared<PatternPuzzle>();
        assert(0); // TODO: implement this
        return puzzle;
    }
    case PATHING: {
        std::shared_ptr<PathingPuzzle> puzzle;
        puzzle = std::make_shared<PathingPuzzle>();
        assert(0); // TODO: implement this
        return puzzle;
    }
    default:
        assert(0); // Should never get here
    } 
}

bool Puzzle::getSuccess() {
    return success;
}

void Puzzle::setSuccess(bool success) {
    this->success = success;
}

LogicPuzzle::LogicPuzzle() : correct_entity(NULL),
                             last_selected(NULL),
                             display_text(false)
{
}

LogicPuzzle::~LogicPuzzle() {
    for (auto it = entities.begin(); it != entities.end(); it++) {
        delete *it;
    }
}

                                  

void LogicPuzzle::notifyPosition(ColRow pos) {

}

void LogicPuzzle::notifySelect(Entity *selected_entity) {
    for (int i = 0; i < entities.size(); i++) {
        Entity *ptr = entities.at(i);
        if (selected_entity == ptr) {
            last_selected = ptr;
            info = logic_puzzle_hints[i];
            display_text = true;
            return;
        }
    }

    last_selected = NULL;
    display_text = false;
}

void LogicPuzzle::notifyKey(char c) {
    if (c == 'F' || c == 'f') {
        if (last_selected && last_selected == correct_entity) {
            setSuccess(true);
            info = "You have won this puzzle.\n";
            display_text = true;
            return;
        }
        else {
            info = "Sorry, you picked the wrong statue, try again!\n";
            display_text = true;
            return;
        }
    }
    else if (c == 'G' || c == 'g') {
        display_text = false;
        return;
    }
}

void LogicPuzzle::draw(Program *prog, MatrixStack *P, MatrixStack *MV,
                       Camera *cam, draw::Text *text, GLFWwindow *window) {
    if (display_text) {
        text->draw(*prog, *window, info, 0, 0);
    }

    for (auto it = entities.begin(); it != entities.end(); it++) {
        Entity *ptr = *it;
        if (ptr->selected) {
            glUniform1i(prog->getUniform("uRedder"), 1);
        }
        else {
            glUniform1i(prog->getUniform("uRedder"), 0);
        }
        
        MV->pushMatrix();
        MV->multMatrix(ptr->getRotation());
        MV->worldTranslate(ptr->getPosition(), ptr->getRotation());
        MV->scale(0.005f);
        glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE,
                           MV->topMatrix().data());
        ptr->getDrawable().draw(prog, P, MV, cam);
        MV->popMatrix();
    }

    glUniform1i(prog->getUniform("uRedder"), 0);
}

void PatternPuzzle::notifyPosition(ColRow pos) {

}

void PatternPuzzle::notifySelect(Entity *selected_entity) {
}


void PathingPuzzle::notifyPosition(ColRow pos) {

}

void PathingPuzzle::notifySelect(Entity *selected_entity) {
}


