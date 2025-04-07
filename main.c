#include <grrlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 1000
#define MAX_NORMALS 1000
#define MAX_UVS 1000
#define MAX_LINE_LENGTH 256

float vertices[MAX_VERTICES][3];
float normals[MAX_NORMALS][3];
float uvs[MAX_UVS][2];

void parseObj(const char* filename, float vertices[MAX_VERTICES][3], float normals[MAX_NORMALS][3], float uvs[MAX_UVS][2]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int vertexIndex = 0, normalsIndex = 0, uvsIndex = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "v ", 2) == 0) {
            sscanf(line + 2, "%f %f %f", &vertices[vertexIndex][0], &vertices[vertexIndex][1], &vertices[vertexIndex][2]);
            vertexIndex++;
        } else if (strncmp(line, "vn ", 3) == 0) {
            sscanf(line + 3, "%f %f %f", &normals[normalsIndex][0], &normals[normalsIndex][1], &normals[normalsIndex][2]);
            normalsIndex++;
        } else if (strncmp(line, "vt ", 3) == 0) {
            sscanf(line + 3, "%f %f", &uvs[uvsIndex][0], &uvs[uvsIndex][1]);
            uvsIndex++;
        }
    }

    fclose(fp);
}

int main(int argc, char **argv) {
    // Initialize GRRLIB
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF); // Black background

    // Load the cube data
    parseObj("cube.obj", vertices, normals, uvs);

    // Main loop
    while (1) {
        GRRLIB_2dMode(); // Switch to 2D mode for rendering
        GRRLIB_Camera3dSettings(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f); // Set camera

        GRRLIB_3dMode(0.1f, 100.0f, 45.0f, true, false); // Switch to 3D mode

        // Draw the cube
        GRRLIB_SetLightAmbient(0x404040); // Set ambient light
        for (int i = 0; i < MAX_VERTICES && vertices[i][0] != 0; i++) {
            GRRLIB_DrawCube(vertices[i][0], vertices[i][1], vertices[i][2], 1.0f, 0xFFFFFF); // Draw each vertex
        }

        GRRLIB_Render(); // Render the frame
    }

    // Clean up
    GRRLIB_Exit();
    return 0;
}