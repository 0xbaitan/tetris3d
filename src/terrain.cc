#include "include/terrain.h"

Terrain::Terrain(const char *heightMapPath, const char *texturePath) {
    LoadHeightMap(heightMapPath, 32, 32, 32);
    AssignIndices(32, 32);
    material.k_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    material.k_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    material.k_specular = glm::vec3(0.8f, 0.8f, 0.8f);
    material.shininess = 32.0f;
    Texture2D* terrain_tex_diffuse = new Texture2D(texturePath, "texture_diffuse");
    terrain_tex_diffuse->LoadTexture();
    Texture2D* terrain_tex_specular = new Texture2D(texturePath, "texture_specular");
    terrain_tex_specular->LoadTexture();
    textures.push_back(terrain_tex_diffuse);
    textures.push_back(terrain_tex_specular);
   terrain = new Mesh(&vertices[0], &indices[0], textures, material, vertices.size(), indices.size());
}

int Terrain::GetFileLength(std::istream &file) {
    int pos = file.tellg();
    file.seekg(0, std::ios::end);
    int length = file.tellg();
    // Restore the position of the get pointer
    file.seekg(pos);

    return length;
}

float Terrain::GetHeightValue(const unsigned char *data, unsigned char numBytes) {
    switch (numBytes) {
    case 4:
        return (unsigned char)(data[0]) / (float)0xFF;
        break;
    case 2:
        return (unsigned short)(data[1] << 8 | data[0]) / (float)0xFFFF;
        break;
    case 1:
        return (unsigned int)(data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0]) / (float)0xFFFFFFFF;
        break;
    default:
    break;
    }
    return 0.0f;
}

void Terrain::AssignIndices(unsigned int width, unsigned int height) {
    for (unsigned int j = 0; j < height - 1; j++) {
        for (unsigned int i = 0; i < width - 1; i++) {
            indices.insert(indices.end(), {j * width + i, j * width + (i + 1), (j + 1) * width + i});
            indices.insert(indices.end(), {j * width + (i + 1), (j + 1) * width + i, (j + 1) * width + (i + 1)});
        }
    }
    printf("%u\n", indices.size());
}


bool Terrain::LoadHeightMap(const char *heightMapPath, unsigned char bitsPerPixel, unsigned int width, unsigned int height) {

   

    std::ifstream ifs;
    ifs.open(heightMapPath, std::ifstream::binary);

    if (ifs.fail()) {
        printf("Failed to read file\n");
        return false;
    }

    const unsigned char bytesPerPixel = bitsPerPixel / 8;
    const unsigned int fileSize = GetFileLength(ifs)-138;

    // if (expectedFileSize != fileSize) {
    //     printf("Expected file size [%u bytes] differs from actual file size [%u bytes]\n", expectedFileSize, fileSize);
    //     return false;
    // }

    unsigned char *heightMap = new unsigned char[fileSize];
     ifs.seekg(138, std::ios::beg);
    ifs.read((char *)heightMap, fileSize);
    // unsigned int index = 0;
  
    // for (unsigned int i = 0; i<fileSize; i++) {
    //      if (i%4==0) {  printf("\n Pixel %u: ", index++); }
    //     printf("%u ", heightMap[i]);
       
    // }
    if (ifs.fail()) {
        printf("An error occured while reading from the file.\n");
        ifs.close();
        delete[] heightMap;
        return false;
    }

   // unsigned int numVertices = width * height;
    float terrainBreadthScale = (1.0f / (height - 1)) * TERRAIN_BREADTH;
    float terrainLengthScale = (1.0f / (width - 1)) * TERRAIN_LENGTH;
    for (unsigned int j = 0; j < height; j++) {
        for (unsigned int i = 0; i < width; i++) {
            unsigned int index = j * width + i;
            float heightValue = GetHeightValue(&heightMap[index*bytesPerPixel], bytesPerPixel);
         //   printf("%f \n", heightValue);
            float s = (i / (float)(width - 1));
            float t = (j / (float)(height - 1));

            float x = s * TERRAIN_BREADTH;
            float y = heightValue * TERRAIN_HEIGHT;
            float z = t * TERRAIN_LENGTH;

            float nx = 0.0f;
            float ny = 1.0f;
            float nz = 0.0f;

           // printf("x: %f, y: %f, z: %f\n", s, y, t);

            vertices.insert(vertices.end(), {x, heightValue, z, nx, ny, nz, s, t});
        }
    }
    return true;
}
