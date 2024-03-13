#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <span>

const int screenWidth = 80;    // Ширина экрана
const int screenHeight = 40;   // Высота экрана
const float aspectRatio = (float)screenHeight / screenWidth;

struct Vec3D {
    float x, y, z;
};

struct Triangle {
    Vec3D p[3];
};

struct Mesh {
    Triangle* tris;
    int nTris;

    Mesh(int n = 0) : nTris(n) { tris = new Triangle[nTris]; }
    ~Mesh() { delete[] tris; }
};

struct Mat4x4 {
    float m[4][4] = { 0 };
};

class Engine3D {
private:
    Mesh cube;
    Mat4x4 projMatrix;
    float theta;

    // Функция умножения матрицы на вектор
    Vec3D MultiplyMatrixVector(const Vec3D& i, const Mat4x4& m) {
        Vec3D v;
        v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
        v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
        v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
        float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
        
        if (w != 0.0f) {
            v.x /= w; v.y /= w; v.z /= w;
        }
        
        return v;
    }

    // Функция проецирования 3D точек на 2D плоскость
    void ProjectMeshTo2D() {
        char screen[screenWidth * screenHeight];
        for (int i = 0; i < screenWidth * screenHeight; i++) screen[i] = ' ';
        
        for (int i = 0; i < cube.nTris; ++i) {
            auto& tri = cube.tris[i];

            Triangle projTri, transTri;

            // Поворот
            transTri.p[0] = MultiplyMatrixVector(tri.p[0], projMatrix);
            transTri.p[1] = MultiplyMatrixVector(tri.p[1], projMatrix);
            transTri.p[2] = MultiplyMatrixVector(tri.p[2], projMatrix);

            // Проецирование на 2D
            projTri.p[0] = { transTri.p[0].x, transTri.p[0].y, 0 };
            projTri.p[1] = { transTri.p[1].x, transTri.p[1].y, 0 };
            projTri.p[2] = { transTri.p[2].x, transTri.p[2].y, 0 };

            // Масштабирование на размер экрана
            projTri.p[0].x += 1.0f; projTri.p[0].y += 1.0f;
            projTri.p[1].x += 1.0f; projTri.p[1].y += 1.0f;
            projTri.p[2].x += 1.0f; projTri.p[2].y += 1.0f;
            projTri.p[0].x *= 0.5f * (float)screenWidth;
            projTri.p[0].y *= 0.5f * (float)screenHeight * aspectRatio;
            projTri.p[1].x *= 0.5f * (float)screenWidth;
            projTri.p[1].y *= 0.5f * (float)screenHeight * aspectRatio;
            projTri.p[2].x *= 0.5f * (float)screenWidth;
            projTri.p[2].y *= 0.5f * (float)screenHeight * aspectRatio;

            // Преобразование координаты y в экранную систему координат
            projTri.p[0].y = screenHeight - projTri.p[0].y;
            projTri.p[1].y = screenHeight - projTri.p[1].y;
            projTri.p[2].y = screenHeight - projTri.p[2].y;

            // Рисование треугольника на экране
            DrawTriangle(screen, projTri);
        }

        // Вывод экрана в терминал
        for (int i = 0; i < screenWidth * screenHeight; i++) {
            if (i % screenWidth == 0) std::cout << '\n';
            std::cout << screen[i];
        }
    }

    // Функция рисования треугольника на экране
    void DrawTriangle(char* screen, const Triangle& tri) {
        DrawLine(screen, tri.p[0], tri.p[1]);
        DrawLine(screen, tri.p[1], tri.p[2]);
        DrawLine(screen, tri.p[2], tri.p[0]);
    }

    // Функция рисования линии на экране (алгоритм Брезенхэма)
    void DrawLine(char* screen, const Vec3D& p1, const Vec3D& p2) {
        int x0 = (int)p1.x;
        int y0 = (int)p1.y;
        int x1 = (int)p2.x;
        int y1 = (int)p2.y;

        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            int index = y0 * screenWidth + x0;
            if (index >= 0 && index < screenWidth * screenHeight)
                screen[index] = '#';
            
            if (x0 == x1 && y0 == y1) break;
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x0 += sx; }
            if (e2 < dx) { err += dx; y0 += sy; }
        }
    }

public:
    Engine3D() : theta(0) {
        // Создание куба
        cube.nTris = 12;
        cube.tris = new Triangle[cube.nTris];

        // Задание вершин куба
        Vec3D vertices[8];
        vertices[0] = { -1, -1, -1 };
        vertices[1] = { -1,  1, -1 };
        vertices[2] = {  1,  1, -1 };
        vertices[3] = {  1, -1, -1 };
        vertices[4] = { -1, -1,  1 };
        vertices[5] = { -1,  1,  1 };
        vertices[6] = {  1,  1,  1 };
        vertices[7] = {  1, -1,  1 };

        // Задание граней куба
        int indices[36] = {
            0, 1, 2, 0, 2, 3,
            4, 5, 6, 4, 6, 7,
            0, 1, 5, 0, 5, 4,
            2, 3, 7, 2, 7, 6,
            0, 3, 7, 0, 7, 4,
            1, 2, 6, 1, 6, 5
        };

        // Заполнение граней куба из вершин
        for (int i = 0; i < cube.nTris; ++i) {
            cube.tris[i].p[0] = vertices[indices[i * 3]];
            cube.tris[i].p[1] = vertices[indices[i * 3 + 1]];
            cube.tris[i].p[2] = vertices[indices[i * 3 + 2]];
        }

        // Установка матрицы проекции
        float fovRad = 1.0f / tanf(45.0f * 0.5f * 3.14159f / 180.0f);
        projMatrix.m[0][0] = aspectRatio * fovRad;
        projMatrix.m[1][1] = fovRad;
        projMatrix.m[2][2] = 0;
        projMatrix.m[3][2] = -1.0f;
        projMatrix.m[2][3] = -0.5f;
    }

    // Функция запуска визуализации куба
    void Run() {
        while (true) {
            // Очистка экрана
            std::system("clear");

            // Вращение куба
            theta += 0.0001f; // Уменьшаем скорость вращения
            Mat4x4 rotZMatrix;
            rotZMatrix.m[0][0] = cosf(theta); rotZMatrix.m[0][1] = -sinf(theta);
            rotZMatrix.m[1][0] = sinf(theta); rotZMatrix.m[1][1] = cosf(theta);
            rotZMatrix.m[2][2] = 1;
            rotZMatrix.m[3][3] = 1;

            // Применение вращения к вершинам куба
            for (int i = 0; i < cube.nTris; ++i) {
                for (int j = 0; j < 3; ++j) {
                    auto& vertex = cube.tris[i].p[j];
                    vertex = MultiplyMatrixVector(vertex, rotZMatrix);
                }
            }

            // Отображение куба на экране
            ProjectMeshTo2D();

            // Задержка для вращения
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Увеличиваем время задержки
        }
    }

};

int main() {
    Engine3D engine;
    engine.Run();
    return 0;
}