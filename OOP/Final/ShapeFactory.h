#pragma once
#include "IShape.h"
#include "IPoint.h"
#include "ISize.h"
#include "Elipse.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"
#include "Polygon.h"
#include "Triangle.h"
#include <random>


class ShapeFactory {


public:

    
    template<typename... Args>
    static IShape* create(IShape::ShapeType type, Args... args) {
        switch (type)
        {
        case IShape::Rectangle:
            return new Rectangle(args...);
            break;
        case IShape::Elipse:
            return new Elipse(args...);
            break;
        case IShape::Circle:
            return new Circle(args...);
            break;
        case IShape::Square:
            return new Square(args...);
            break;
        case IShape::Polygon:
            return new Polygon(args...);
            break;
        case IShape::Triangle:
            return new Triangle(args...);
        default:
            return nullptr; // Return nullptr or throw an exception for invalid shape type
        }
    }
public:
    static void DrawShapes(SDL_Renderer* renderer) {
        std::random_device rd;  // Obtain a random number from hardware
        std::mt19937 gen(rd()); // Seed the generator

        std::uniform_int_distribution<> distr_shape(1, 5); // Define the range
        IShape::ShapeType type = static_cast<IShape::ShapeType>(distr_shape(gen));

        std::uniform_int_distribution<> distr_pos(0, 600); // Define the range for position
        int cx = distr_pos(gen);
        int cy = distr_pos(gen);

        std::uniform_int_distribution<> distr_size(50, 150); // Define the range for size
        int sh = distr_size(gen);
        int sw = distr_size(gen);

        std::uniform_real_distribution<> distr_scale(50, 150); // Define the range for scale
        float scale = distr_scale(gen);

        std::uniform_int_distribution<> distr_angle(0, 180); // Define the range for angle
        float angle = distr_angle(gen);

        std::uniform_int_distribution<> distr_sides(3, 15); // Define the range for polygon sides
        int n = distr_sides(gen);

        std::vector<Point> pol(n);
        for (int i = 0; i < n; i++) {
            int px = distr_pos(gen);
            int py = distr_pos(gen);
            pol[i] = Point(px, py);
        }

        std::vector<Point> tri(3);
        for (int i = 0; i < 3; i++) {
            int px = distr_pos(gen);
            int py = distr_pos(gen);
            tri[i] = Point(px, py);
        }

        Point center(cx, cy);
        Size size(sw, sh);

        IShape* shape = nullptr;
        switch (type) {
        case IShape::Rectangle:
            //shape = create(type, size, center, angle);
            shape = new Rectangle(size, center, angle);
            break;
        case IShape::Elipse:
            //shape = create(type, size, center, angle);
            shape = new Elipse(size, center, angle);
            break;
        case IShape::Circle:
            //shape = create(type, size, center, angle);
            shape = new Circle(center, scale);
            break;
        case IShape::Square:
            //shape = create(type, size, center, angle);
            shape = new Square(size, center, angle);
            break;
        case IShape::Polygon:
            //shape = create(type, size, center, angle);
            shape = new Polygon(pol);
            break;
        case IShape::Triangle:
            //shape = create(type, size, center, angle);
            shape = new Triangle(tri);
            break;
        default:
            break;
        }

        if (shape != nullptr) {
            shape->draw(renderer);
            //delete shape;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    
};