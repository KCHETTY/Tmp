#include "../Inc/Render.hpp"


GLFWwindow *Render::window = nullptr;
Camera *Render::camera = nullptr;

bool Render::firstmouse = true;
GLfloat Render::deltaTime = 0.0f;
GLfloat Render::lastFrame = 0.0f;

GLfloat Render::lastX = 0.0f;
GLfloat Render::lastY = 0.0f;

bool Render::keys[1024];


Render::Render()
{
    return ;
}

Render::~Render()
{
    return ;
}

void Render::init()
{
    //glfwSetErrorCallback(OnError);

    if( !glfwInit() )
    {
        std::cout << "Bad news1" << std::endl;
        exit(1);
    }

    // open a window with GLFW, sets required GLFW options
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    Render::window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "render", nullptr, nullptr ); //Create GLFW window

    if ( !window ) // Check if window was created
    {
        std::cout << "Bad news2" << std::endl;
        glfwTerminate(); // Terminate GLFW
        exit(2);
    }

    glfwMakeContextCurrent( Render::window ); // Make the windows context current
    glfwGetFramebufferSize( Render::window, &this->Screen_Width, &this->Screen_Height );

    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if( glewInit() != GLEW_OK )
    {
        std::cout << "Bad news 3" << std::endl;
        exit(3);
    }

    glfwSetKeyCallback( Render::window, KeyCallback);
    glfwSetScrollCallback( Render::window, ScrollCallback);
    glfwSetCursorPosCallback( Render::window, MouseCallback);

    glfwSetInputMode( Render::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    std::cout << "Im Here" << std::endl;

    this->shader.compile_shaders("/nfs/zfs-student-6/users/kchetty/Desktop/Tmp/Shaders/Colour_Shading.vert", "/nfs/zfs-student-6/users/kchetty/Desktop/Tmp/Shaders/Colour_Shasiner.frag");

    Render::camera = new Camera( glm::vec3( 0.0f, 0.0f, 3.0f) );
    Render::lastX = SCREEN_WIDTH / 2.0f;
    Render::lastY = SCREEN_HEIGHT / 2.0f;

    glViewport( 0.0f, 0.0f, this->Screen_Width, this->Screen_Height ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalized to pixels.
}

void Render::render()
{
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    GLfloat vertices[] =
    {
        //Vertices                  //Texture Co-Ordinates
        -0.5f, -0.5f, -0.5f,         0.0f, 0.0f,  //
        0.5f, -0.5f, -0.5f,          1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,           1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,          0.0f, 1.0f,

        -0.5f, -0.5f, 0.5f,         0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,          1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,           1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,          0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f,         1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,          1.0f, 1.0f,
        -0.5f,-0.5f, -0.5f,           0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,          0.0f, 0.0f,

        0.5f, 0.5f, 0.5f,         1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,          1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,           0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,          0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,         0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,          1.0f, 1.0f,
        0.5f, -0.5f, 0.5f,           1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,          0.0f, 0.0f,

        -0.5f, 0.5f, -0.5f,         0.0f, 1.0f,
        0.5f, 0.5f, -0.5f,          1.0f, 1.0f,
        0.5f, 0.5f, 0.5f,           1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,          0.0f, 0.0f,
    };

    GLuint indices[] =
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    glm::vec3 CubePos [] =
    {
        glm::vec3( 0.0f, 0.0f, -4.0f),
    };

    GLuint VBO = 0, VAO = 0, EBO = 0;
    glGenVertexArrays( 1, &VAO ); // Generates a Vertex Array Object
    glGenBuffers( 1, &VBO ); // Generates a VBO Buffer
    glGenBuffers( 1, &EBO ); // Generates a EBO Buffer

    std::cout << "VBO " << VBO << " VAO " << VAO << std::endl;

    // Binds VAO Vertex Array
    glBindVertexArray( VAO );

    //binds VBO
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    //Copies Vertex data into VBO Bound Memory
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    // binds EBO
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    //Copies Indicies data into EBO bound memory
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid *) 0 );
    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid *)( 3 * sizeof(GLfloat) ) );
    glEnableVertexAttribArray( 1 );

    glBindBuffer( GL_ARRAY_BUFFER, 0);
    glBindVertexArray( 0 );

    GLuint texture;

    int width, height;
    glGenTextures(1, &texture);
    glBindTexture( GL_TEXTURE_2D, texture);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    unsigned char *image = SOIL_load_image("/nfs/zfs-student-6/users/kchetty/Desktop/Tmp/Textures/wildtextures-creased-gilded-decorative-paper-texture.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap( GL_TEXTURE_2D );
    SOIL_free_image_data( image );
    glBindTexture( GL_TEXTURE_2D, 0);

    glm::mat4 projection;

    std::cout << "Im Here" << std::endl;
    while ( !glfwWindowShouldClose( window ) ) // loop until user closes the window
    {
        GLfloat current_time = glfwGetTime();
        Render::deltaTime = current_time - Render::lastFrame;
        Render::lastFrame = current_time;

        glfwPollEvents( ); // poll for and process events
        DoMovement();

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //

        glUseProgram( shader.GetProgramID() );

        glActiveTexture( GL_TEXTURE0 );
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i( glGetUniformLocation(shader.GetProgramID(), "OurText"), 0 );

        projection = glm::perspective( Render::camera->GetZoom() , (GLfloat)this->Screen_Width / (GLfloat)this->Screen_Height, 1.0f, 10000.0f);

        //glm::mat4 model_matrix;
        glm::mat4 view_matrix;

        //model_matrix = glm::rotate( model_matrix, (GLfloat)glfwGetTime() * 1.0f, glm::vec3( 0.5f, 1.0f, 0.0f ));
        //view_matrix = glm::translate( view_matrix, glm::vec3( 0.0f, 0.0f, -2.0f) );
        view_matrix = camera->GetViewMatrix();

        GLint modelLoc = glGetUniformLocation( shader.GetProgramID(), "model");
        GLint projLoc = glGetUniformLocation( shader.GetProgramID(), "projection");
        GLint viewLoc = glGetUniformLocation( shader.GetProgramID(), "view");


        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ));
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view_matrix ));

        /*glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 36);
        glBindVertexArray( 0 );*/

        glBindVertexArray( VAO );

        GLfloat tmp = -4.0f;
        for (int y = 0; y < 16; y++)
        {
            for (GLfloat x = -9.0f; x < 8.0f; x++)
            {
                CubePos[0] = glm::vec3(x, 0.0f , tmp);

                glm::mat4 model;

                model = glm::translate(model, CubePos[0]);
                //GLfloat angle = 20.0f * x;
                //model = glm::rotate( model, angle, glm::vec3( 0.0f, 0.0f, 0.0f ));
                glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ));

                glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            }
            tmp -= 1.0f;
        }
        glBindVertexArray( 0 );

        glfwSwapBuffers( window ); // swap front and back buffers
        std::cout << "X " << lastX << " Y " << lastY << std::endl;
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers( 1, &VBO );
    //glDeleteBuffers( 1, &EBO );

    glfwTerminate();
}

void Render::KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose( window, GL_TRUE);

    if ( key >= 0 && key < 1024)
    {
        if ( GLFW_PRESS == action )
            keys[key] = true;
        else if ( GLFW_RELEASE == action )
            keys[key] = false;
    }
}

void Render::ScrollCallback( GLFWwindow *window, double xOffset, double yOffset )
{
    camera->ProcessMouseScroll( yOffset );
}

void Render::MouseCallback( GLFWwindow *window, double posX, double posY )
{
    if ( firstmouse )
    {
        lastX = posX;
        lastY = posY;
        firstmouse = false;
    }

    GLfloat xOffset = posX - lastX;
    GLfloat yOffset = lastY - posY;

    lastX = posX;
    lastY = posY;

    camera->ProcessMouseMovement( xOffset, yOffset );
}

void Render::DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
        camera->ProcessKeyboard( Camera_movement::FORWARD, deltaTime );
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
        camera->ProcessKeyboard( Camera_movement::BACKWARD, deltaTime );
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
        camera->ProcessKeyboard( Camera_movement::LEFT, deltaTime );
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
        camera->ProcessKeyboard( Camera_movement::RIGHT, deltaTime );
}
