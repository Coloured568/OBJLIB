#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 1000
#define MAX_NORMALS 1000
#define MAX_UVS 1000
#define MAX_LINE_LENGTH 256

float cubeVerts[MAX_VERTICES][3];

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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <obj_file>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1];
    float vertices[MAX_VERTICES][3] = {0};
    float normals[MAX_NORMALS][3] = {0};
    float uvs[MAX_UVS][2] = {0};

    printf("OBJ Parser\n");
    printf("==========\n");

    parseObj(filename, vertices, normals, uvs);

    for (int i = 0; i < MAX_VERTICES && vertices[i][0] != 0; i++) {
        printf("Vertex %d: %f %f %f\n", i, vertices[i][0], vertices[i][1], vertices[i][2]);
    }

    return 0;
}