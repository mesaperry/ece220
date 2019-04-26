#include "shape.hpp"




//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 

Shape::Shape(string name){
	name_ = name;
}
string Shape::getName(){
	return name_;
}

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Rectangle::Rectangle(double width, double length):Shape("Rectangle"){
	width_ = width;
	length_ = length;
}
double Rectangle::getArea()const{return width_*length_;}
double Rectangle::getVolume()const{return 0;}
Rectangle Rectangle::operator + (const Rectangle& rec){
	Rectangle* ptr = new Rectangle(rec.width_ + width_, rec.length_ + length_);
	return *ptr;
}
Rectangle Rectangle::operator - (const Rectangle& rec){
	printf("%lf %lf %lf %lf\n", width_, rec.width_, length_, rec.length_);
	printf("%lf %lf\n", std::max((double)0, (width_ - rec.width_)), std::max((double)0, (length_ - rec.length_)));
	Rectangle* ptr = new Rectangle(std::max((double)0, (width_ - rec.width_)), std::max((double)0, (length_ - rec.length_)));
	return *ptr;
}


double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Circle::Circle(double radius):Shape("Circle"){
	radius_ = radius;
}
double Circle::getArea()const{return M_PI * radius_ * radius_;}
double Circle::getVolume()const{return 0;}
Circle Circle::operator + (const Circle& rec){
	Circle* ptr = new Circle(rec.radius_ + radius_);
	return *ptr;
}
Circle Circle::operator - (const Circle& rec){
	Circle* ptr = new Circle(std::max((double)0, radius_ - rec.radius_));
	return *ptr;
}


double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Sphere::Sphere(double radius):Shape("Sphere"){
	radius_ = radius;
}
double Sphere::getArea()const{return (double)4 * M_PI * radius_ * radius_;}
double Sphere::getVolume()const{return ((double)4/(double)3 * radius_ * radius_ * radius_ * M_PI);}
Sphere Sphere::operator + (const Sphere& rec){
	Sphere* ptr = new Sphere(rec.radius_ + radius_);
	return *ptr;
}
Sphere Sphere::operator - (const Sphere& rec){
	Sphere* ptr = new Sphere(std::max((double)0, radius_ - rec.radius_));
	return *ptr;
}


double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism"){
	width_ = width;
	length_ = length;
	height_ = height;
}
double RectPrism::getArea()const{return 2*(width_*length_ + length_*height_ + width_*height_);}
double RectPrism::getVolume()const{return width_*length_*height_;}
RectPrism RectPrism::operator + (const RectPrism& rec){
	RectPrism* ptr = new RectPrism(rec.width_ + width_, rec.length_ + length_, rec.height_ + height_);
	return *ptr;
}
RectPrism RectPrism::operator - (const RectPrism& rec){
	RectPrism* ptr = new RectPrism(std::max((double)0, (width_ - rec.width_)), std::max((double)0, (length_ - rec.length_)), std::max((double)0, (height_ - rec.height_)));
	return *ptr;
}


double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}


 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	string name;
	double r, length, width, height;
	std::vector<Shape*> vec;
	ifstream ifs (file_name, std::ifstream::in);
	while(1){
		ifs >> name;
		if(ifs.eof()){
			break;
		}
		if(name == "Rectangle"){
			ifs >> length >> width;
			Shape* shape_ptr = new Rectangle(length, width);
			vec.push_back(shape_ptr);
		}
		if(name == "Circle"){
			ifs >> r;
			Shape* shape_ptr = new Circle(r);
			vec.push_back(shape_ptr);
		}
		if(name == "Sphere"){
			ifs >> r;
			Shape* shape_ptr = new Sphere(r);
			vec.push_back(shape_ptr);
		}
		if(name == "RectPrism"){
			ifs >> length >> width >> height;
			Shape* shape_ptr = new RectPrism(length, width, height);
			vec.push_back(shape_ptr);
		}
	}
	ifs.close();
	return vec; // please remeber to modify this line to return the correct value
}

// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	for(int i = 0; i < shapes.size(); i++){
		if(shapes[i]->getArea() > max_area){
			max_area = shapes[i]->getArea();
		}
	}
	return max_area;
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	for(int i = 0; i < shapes.size(); i++){
		if(shapes[i]->getVolume() > max_volume){
			max_volume = shapes[i]->getVolume();
		}
	}
	return max_volume;
}

