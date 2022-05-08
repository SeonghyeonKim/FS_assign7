#pragma once

#ifndef COURSE
#define COURSE
#include <iostream>
typedef class CourseResistration {
public:
	char CourseId[11]; char StudentId[11]; int NumberCredit;
	float Grade; char temp[16]; ;

	CourseResistration();
	CourseResistration(char*, char*, int, float);
	friend std::istream& operator >> (std::istream& stream, CourseResistration& c);
	friend std::ostream& operator << (std::ostream& stream, CourseResistration& c);
} CR;

CourseResistration::CourseResistration() {
	CourseId[0] = 0; StudentId[0] = 0; NumberCredit = 0;
	Grade = 0; temp[0] = 0;
}

CourseResistration::CourseResistration(char* cid, char* sid, int nc, float gr) {
	strcpy(CourseId, cid);
	strcpy(StudentId, sid);
	NumberCredit = nc;
	Grade = gr;
}
#endif

