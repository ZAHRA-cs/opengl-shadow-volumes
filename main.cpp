#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include <glm/gtx/rotate_vector.hpp>

#define ERROR_LOG(ErrorMessage) \
    glfwTerminate();std::cout<<ErrorMessage<<std::endl; \
    return -1;

// Time and camera variables
GLfloat deltaTime = 0.0f, lastTime = 0.0f;
glm::mat4 modelMat = glm::mat4(1.0f);
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

// Cube vertices with position, color, and normals
GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
};

// LARGER ground plane - different color (dark blue-gray)
GLfloat groundVertices[] = {
    -5.0f, -0.5f, -5.0f, 0.2f, 0.3f, 0.4f, 0.0f, 1.0f, 0.0f,
     5.0f, -0.5f, -5.0f, 0.2f, 0.3f, 0.4f, 0.0f, 1.0f, 0.0f,
     5.0f, -0.5f,  5.0f, 0.2f, 0.3f, 0.4f, 0.0f, 1.0f, 0.0f,
     5.0f, -0.5f,  5.0f, 0.2f, 0.3f, 0.4f, 0.0f, 1.0f, 0.0f,
    -5.0f, -0.5f,  5.0f, 0.2f, 0.3f, 0.4f, 0.0f, 1.0f, 0.0f,
    -5.0f, -0.5f, -5.0f, 0.2f, 0.3f, 0.4f, 0.0f, 1.0f, 0.0f,
};

// Cube topology data
GLfloat cubeCorners[] = {
    -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f
};

GLuint faceIndices[] = {
    0, 3, 2,  2, 1, 0,
    4, 5, 6,  6, 7, 4,
    0, 1, 5,  5, 4, 0,
    3, 7, 6,  6, 2, 3,
    0, 4, 7,  7, 3, 0,
    1, 2, 6,  6, 5, 1
};

struct EdgeData {
    int v0, v1;
    int face0, face1;
};

EdgeData silhouetteEdges[] = {
    {0, 3, 0, 9},   {3, 2, 0, 7},   {2, 1, 1, 10},  {1, 0, 1, 4},
    {4, 5, 2, 4},   {5, 6, 2, 11},  {6, 7, 3, 6},   {7, 4, 3, 8},
    {0, 4, 5, 8},   {1, 5, 4, 11},  {6, 2, 7, 10},  {3, 7, 6, 9}
};
const int edgeCount = 12;

// OpenGL objects
GLuint cubeVAO, cubeVBO;
GLuint groundVAO, groundVBO;
GLuint lightCubeVAO;
GLuint shadowVAO, shadowVBO;

std::vector<GLfloat> shadowVolumeData;

// Setup cube buffers
static void SetupCubeBuffers()
{
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Setup light cube
static void SetupLightCube()
{
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Setup ground plane
static void SetupGroundPlane()
{
    glGenVertexArrays(1, &groundVAO);
    glGenBuffers(1, &groundVBO);
    glBindVertexArray(groundVAO);
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Setup shadow volume
static void SetupShadowVolume()
{
    glGenVertexArrays(1, &shadowVAO);
    glGenBuffers(1, &shadowVBO);
    glBindVertexArray(shadowVAO);
    glBindBuffer(GL_ARRAY_BUFFER, shadowVBO);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int viewportWidth, viewportHeight;
static void SetViewport(GLFWwindow* window)
{
    glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
    glViewport(0, 0, viewportWidth, viewportHeight);
}

glm::vec3 lightPos = glm::vec3(3.0f, 3.0f, 0.0f);  // Far away and more  higher

// Build shadow volume using Z-FAIL with caps
static void BuildShadowVolume(glm::vec3 lightWorldPos, glm::mat4 objectMat)
{
    shadowVolumeData.clear();
    const float extrusionLen = 50.0f;  // more thn 30.0f to avoid clipping issues

    glm::vec3 worldVerts[8];
    for (int i = 0; i < 8; i++) {
        glm::vec4 pos = objectMat * glm::vec4(
            cubeCorners[i * 3], cubeCorners[i * 3 + 1], cubeCorners[i * 3 + 2], 1.0f);
        worldVerts[i] = glm::vec3(pos);
    }

    bool litFace[12];
    for (int f = 0; f < 12; f++) {
        int i0 = faceIndices[f * 3];
        int i1 = faceIndices[f * 3 + 1];
        int i2 = faceIndices[f * 3 + 2];

        glm::vec3 p0 = worldVerts[i0];
        glm::vec3 p1 = worldVerts[i1];
        glm::vec3 p2 = worldVerts[i2];

        glm::vec3 norm = glm::normalize(glm::cross(p1 - p0, p2 - p0));
        glm::vec3 toLight = glm::normalize(lightWorldPos - p0);

        litFace[f] = (glm::dot(norm, toLight) > 0.0f);
    }

    // Front cap
    for (int f = 0; f < 12; f++) {
        if (litFace[f]) {
            int i0 = faceIndices[f * 3];
            int i1 = faceIndices[f * 3 + 1];
            int i2 = faceIndices[f * 3 + 2];

            glm::vec3 v0 = worldVerts[i0];
            glm::vec3 v1 = worldVerts[i1];
            glm::vec3 v2 = worldVerts[i2];

            shadowVolumeData.push_back(v0.x); shadowVolumeData.push_back(v0.y); shadowVolumeData.push_back(v0.z);
            shadowVolumeData.push_back(v1.x); shadowVolumeData.push_back(v1.y); shadowVolumeData.push_back(v1.z);
            shadowVolumeData.push_back(v2.x); shadowVolumeData.push_back(v2.y); shadowVolumeData.push_back(v2.z);
        }
    }

    // Back cap
    for (int f = 0; f < 12; f++) {
        if (litFace[f]) {
            int i0 = faceIndices[f * 3];
            int i1 = faceIndices[f * 3 + 1];
            int i2 = faceIndices[f * 3 + 2];

            glm::vec3 v0 = worldVerts[i0];
            glm::vec3 v1 = worldVerts[i1];
            glm::vec3 v2 = worldVerts[i2];

            glm::vec3 v0e = v0 + glm::normalize(v0 - lightWorldPos) * extrusionLen;
            glm::vec3 v1e = v1 + glm::normalize(v1 - lightWorldPos) * extrusionLen;
            glm::vec3 v2e = v2 + glm::normalize(v2 - lightWorldPos) * extrusionLen;

            shadowVolumeData.push_back(v0e.x); shadowVolumeData.push_back(v0e.y); shadowVolumeData.push_back(v0e.z);
            shadowVolumeData.push_back(v2e.x); shadowVolumeData.push_back(v2e.y); shadowVolumeData.push_back(v2e.z);
            shadowVolumeData.push_back(v1e.x); shadowVolumeData.push_back(v1e.y); shadowVolumeData.push_back(v1e.z);
        }
    }

    // Silhouette quads
    for (int e = 0; e < edgeCount; e++) {
        int f0 = silhouetteEdges[e].face0;
        int f1 = silhouetteEdges[e].face1;

        if (litFace[f0] != litFace[f1]) {
            int v0i = silhouetteEdges[e].v0;
            int v1i = silhouetteEdges[e].v1;

            //Swap when face1 is lit
            if (litFace[f1]) {
                std::swap(v0i, v1i);
            }

            glm::vec3 n0 = worldVerts[v0i];
            glm::vec3 n1 = worldVerts[v1i];

            glm::vec3 f0 = n0 + glm::normalize(n0 - lightWorldPos) * extrusionLen;
            glm::vec3 f1 = n1 + glm::normalize(n1 - lightWorldPos) * extrusionLen;

            shadowVolumeData.push_back(n0.x); shadowVolumeData.push_back(n0.y); shadowVolumeData.push_back(n0.z);
            shadowVolumeData.push_back(f0.x); shadowVolumeData.push_back(f0.y); shadowVolumeData.push_back(f0.z);
            shadowVolumeData.push_back(f1.x); shadowVolumeData.push_back(f1.y); shadowVolumeData.push_back(f1.z);

            shadowVolumeData.push_back(n0.x); shadowVolumeData.push_back(n0.y); shadowVolumeData.push_back(n0.z);
            shadowVolumeData.push_back(f1.x); shadowVolumeData.push_back(f1.y); shadowVolumeData.push_back(f1.z);
            shadowVolumeData.push_back(n1.x); shadowVolumeData.push_back(n1.y); shadowVolumeData.push_back(n1.z);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, shadowVBO);
    glBufferData(GL_ARRAY_BUFFER, shadowVolumeData.size() * sizeof(GLfloat),
        shadowVolumeData.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void RenderCube(Shader& shader, const glm::mat4& cubeMat)
{
    shader.UseProgram();
    glm::mat4 view = camera.GetViewMatrix();
    shader.SetMatrix4fv("view", view);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f),
        static_cast<GLfloat>(viewportWidth) / static_cast<GLfloat>(viewportHeight), 0.1f, 100.0f);
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("transform", cubeMat);
    shader.SetVec3f("LightPos", lightPos);
    shader.SetVec3f("ViewPos", camera.GetPosition());

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

static void RenderGround(Shader& shader)
{
    shader.UseProgram();
    glm::mat4 view = camera.GetViewMatrix();
    shader.SetMatrix4fv("view", view);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f),
        static_cast<GLfloat>(viewportWidth) / static_cast<GLfloat>(viewportHeight), 0.1f, 100.0f);
    shader.SetMatrix4fv("projection", projection);

    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -2.0f));
    shader.SetMatrix4fv("transform", modelMat);
    shader.SetVec3f("LightPos", lightPos);
    shader.SetVec3f("ViewPos", camera.GetPosition());

    glBindVertexArray(groundVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

static void RenderLight(Shader& shader)
{
    shader.UseProgram();
    glm::mat4 view = camera.GetViewMatrix();
    shader.SetMatrix4fv("view", view);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f),
        static_cast<GLfloat>(viewportWidth) / static_cast<GLfloat>(viewportHeight), 0.1f, 100.0f);
    shader.SetMatrix4fv("projection", projection);

    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, lightPos);
    modelMat = glm::scale(modelMat, glm::vec3(0.15f, 0.15f, 0.15f));  // to mke larger
    shader.SetMatrix4fv("transform", modelMat);

    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_STENCIL_BITS, 8);

    GLFWwindow* window = glfwCreateWindow(800, 600, "F23040129", NULL, NULL);
    if (window == NULL) { ERROR_LOG("Failed to create GLFW window") }

    glfwMakeContextCurrent(window);
    if (GLEW_OK != glewInit()) { ERROR_LOG("Failed to init glew") }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);

    SetupCubeBuffers();
    SetupLightCube();
    SetupGroundPlane();
    SetupShadowVolume();

    // DIFF shader file names
    Shader ambientShader = Shader("res/shaders/core.vs", "res/shaders/ambient.fs");
    Shader diffuseShader = Shader("res/shaders/core.vs", "res/shaders/diffuse.fs");
    Shader volumeShader = Shader("res/shaders/volume.vs", "res/shaders/volume.fs");
    Shader lightShader = Shader("res/shaders/light.vs", "res/shaders/light.fs");

    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        SetViewport(window);
        glfwPollEvents();

        glClearColor(0.15f, 0.15f, 0.2f, 1.0f);  // Different background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Light moves in elliptical path
        float time = currentTime * 0.6f;
        lightPos = glm::vec3(
            3.5f * cos(time),
            3.0f,
            2.0f * sin(time)
        );

        // Cube ON GROUND with 45-degree tilt
        glm::mat4 cubeTransform = glm::mat4(1.0f);

        // Position so lowest corner touches ground at Y=-0.5
        cubeTransform = glm::translate(cubeTransform, glm::vec3(0.0f, -0.073f, -2.0f));

        // 45-degree tilt on (1,0,1) axis - SAME as other student
        cubeTransform = glm::rotate(cubeTransform, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));

        // up to mid size
        cubeTransform = glm::scale(cubeTransform, glm::vec3(0.5f, 0.5f, 0.5f));

        BuildShadowVolume(lightPos, cubeTransform);

        //Ambient
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        RenderGround(ambientShader);
        RenderCube(ambientShader, cubeTransform);
        RenderLight(lightShader);

        //Shadow volumes (Z-FAIL)
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LESS);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glStencilMask(0xFF);
        glEnable(GL_CULL_FACE);

        volumeShader.UseProgram();
        glm::mat4 view = camera.GetViewMatrix();
        volumeShader.SetMatrix4fv("view", view);
        glm::mat4 projection = glm::perspective(glm::radians(60.0f),
            static_cast<GLfloat>(viewportWidth) / static_cast<GLfloat>(viewportHeight), 0.1f, 100.0f);
        volumeShader.SetMatrix4fv("projection", projection);

        glBindVertexArray(shadowVAO);

        glCullFace(GL_FRONT);
        glStencilOp(GL_KEEP, GL_INCR, GL_KEEP);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(shadowVolumeData.size() / 3));

        glCullFace(GL_BACK);
        glStencilOp(GL_KEEP, GL_DECR, GL_KEEP);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(shadowVolumeData.size() / 3));

        glBindVertexArray(0);
        glDisable(GL_CULL_FACE);

        //Lighting
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glStencilFunc(GL_EQUAL, 0, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);

        RenderGround(diffuseShader);
        RenderCube(diffuseShader, cubeTransform);

        glDisable(GL_BLEND);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);

        glfwSwapBuffers(window);
    }

    return 1;
}