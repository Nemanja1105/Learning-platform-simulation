#pragma once
#include"Course.h"
#include"CoursePrecondition.h"
#include"CourseInfoFileIO.h"
#include"CourseManagerFileIO.h"
#include"CoursePrecondtionFileIO.h"
#include<vector>


namespace learningPlatform
{
	//kada se kurs obrise gube se njegove informacije
	//posto je on sacuvan u polozenim kursevima dolazi do prekida
	//aplikacije posto se ne moze pronaci kurs sa datim id
	//u ovoj verziji prilikom brisanja kursa brisu se i polozeni kursevi
	//u narednim verzijama ispraviti pogresku
	class CourseAdminInteraction
	{
	public:
		static void showCourses(std::vector<Course>&);//
		static void createCourse(std::vector<Course>&, std::vector<CoursePrecondtion*>&,std::vector<Professor>&);//
		static void deleteCourse(std::vector<Course>&,std::vector<Student>&,std::vector<Professor>&);//
		static void modifyCourse(std::vector<Course>&,std::vector<Professor>&);//
		static void courseSetOperation(std::vector<Course>&,std::vector<Student>&);//
	private:
		CourseAdminInteraction();
		static void printProfHeader();
		static void printProfFooter();
		static void printProf(const Professor&);
		static Professor& profChoise(std::vector<Professor>&);
		
		
	};
}
