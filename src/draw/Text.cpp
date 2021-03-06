#include <draw/Text.hpp>

#define CHECK_ERRORS_THIS_FILE 1
#include <errors.hpp>

namespace draw {

	Text::Text() : txt(""), font_name(""), header("resources/font/"), pix_size(24)
	{		 
	    std::string file = header + font_name;

	    if (FT_Init_FreeType(&ft)) {
	        std::cerr << "Could not init freetype library" << std::endl;
	        exit(-1);
	    }
	 
	    if (FT_New_Face(ft, file.c_str(), 0, &face)) {
	        std::cerr << "Could not open font" << std::endl;
	        exit(-1);
	    }
	      
	    FT_Set_Pixel_Sizes(face, 0, pix_size);      
	    g = face->glyph;
	}

	Text::Text(std::string font, int font_size): txt(""), header("resources/font/") 
	{
		font_name = font;
		pix_size = font_size;

	    std::string file = header + font_name;

	    if (FT_Init_FreeType(&ft)) {
	        std::cerr << "Could not init freetype library" << std::endl;
	        exit(-1);
	    }
	 
	    if (FT_New_Face(ft, file.c_str(), 0, &face)) {
	        std::cerr << "Could not open font" << std::endl;
	        exit(-1);
	    }
	      
	    FT_Set_Pixel_Sizes(face, 0, pix_size);      
	    g = face->glyph;
	}

	Text::~Text() {}

	// folow coords of 0,0 is middle, .9, .9 is top right corner, -.9, -.9, is bottom left corner
	void Text::draw(Program& prog, GLFWwindow& window, std::string display_txt, float x_s, float y_s, float enter_val) {
		int str_size = display_txt.size();

		glUniform1i(prog.getUniform("uTextToggle"), 1);
                CHECK_GL_ERRORS();
	    glActiveTexture(GL_TEXTURE0);
            CHECK_GL_ERRORS();
	    glGenTextures(1, &tex);
        CHECK_GL_ERRORS();
	    glBindTexture(GL_TEXTURE_2D, tex);
	           CHECK_GL_ERRORS();
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	            CHECK_GL_ERRORS();
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	           CHECK_GL_ERRORS();
	    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        CHECK_GL_ERRORS();
	    glGenBuffers(1, &vbo);
	    glEnableVertexAttribArray(prog.getAttribute("wordCoords"));
	    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	    glVertexAttribPointer(prog.getAttribute("wordCoords"), 4, GL_FLOAT, GL_FALSE, 0, 0);
        CHECK_GL_ERRORS();
	    glEnable(GL_BLEND);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        CHECK_GL_ERRORS();
    	glDisable(GL_DEPTH_TEST);

		int w, h;
		glfwGetWindowSize(&window, &w, &h);

	    float sx = 2.0f / w; 
	    float sy = 2.0f / h;

	    const char* cn_str;
	    std::string cplus_str;

	    std::ostringstream convert; 
	    convert << display_txt;
	    cplus_str = convert.str();
	    cn_str = cplus_str.c_str();

	    /*if (sx + x_s + str_size * .07 > 1) {
	    	renderText(cn_str, sx + x_s - .5 * str_size * .07, sy + y_s, sx, sy);
	    }
	    else {   */
            CHECK_GL_ERRORS();
    	renderText(cn_str, sx + x_s, sy + y_s, sx, sy, enter_val);
        CHECK_GL_ERRORS();
	    //} 

        CHECK_GL_ERRORS();
    	glEnable(GL_DEPTH_TEST);
        CHECK_GL_ERRORS();
	    glDisable(GL_BLEND);
        CHECK_GL_ERRORS();
		glUniform1i(prog.getUniform("uTextToggle"), 0);
	}

	void Text::renderText(const char *text, float x, float y, float sx, float sy, float enter_val) {
		float orig_x = x;
		float advancer = g->advance.x >> 6;

	    for(const char *p = text; *p; p++) {
	    	if (*p == '\n') {
	    		y -= (advancer)/enter_val;
	    		x = orig_x;
	    		continue;
	    	}
	        if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
	            continue;
	 
                CHECK_GL_ERRORS();
	        glTexImage2D(
	          GL_TEXTURE_2D,
	          0,
	          GL_ALPHA,
	          g->bitmap.width,
	          g->bitmap.rows,
	          0,
	          GL_ALPHA,
	          GL_UNSIGNED_BYTE,
	          g->bitmap.buffer
	        );
                CHECK_GL_ERRORS();
	        float x2 = x + g->bitmap_left * sx;
	        float y2 = -y - g->bitmap_top * sy;
	        float w = g->bitmap.width * sx;
	        float h = g->bitmap.rows * sy;
	     
	        GLfloat box[4][4] = {
	            {x2,     -y2    , 0, 0},
	            {x2 + w, -y2    , 1, 0},
	            {x2,     -y2 - h, 0, 1},
	            {x2 + w, -y2 - h, 1, 1},
	        };
#if 1	
	        glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
                CHECK_GL_ERRORS();
#endif
#if 0
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(box), box);
                CHECK_GL_ERRORS();
#endif
#if 1
                CHECK_GL_ERRORS();
	        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
                CHECK_GL_ERRORS();
#endif
#if 0
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                CHECK_GL_ERRORS();
                glDrawArrays(GL_TRIANGLES, 0, 6);
                CHECK_GL_ERRORS();
#endif
	        x += (g->advance.x >> 6) * sx;
	        y += (g->advance.y >> 6) * sy;
	    }
	}
}
