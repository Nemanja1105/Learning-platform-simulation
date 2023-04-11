#pragma once
#include<string>
#include"Student.h"

namespace learningPlatform
{
	class CoursePrecondtion
	{
	protected:
		std::string id;
		static std::string lastId;
	public:
		CoursePrecondtion();
		CoursePrecondtion(std::string);
		static void setLastId(std::string);
		bool operator()(const Student&)const;
		virtual std::string getType()const = 0;
		virtual std::string getInfo()const = 0;
		std::string getId()const;
		void setId(std::string);
		friend std::ifstream& operator>>(std::ifstream&, CoursePrecondtion&);
		friend std::ostream& operator<<(std::ostream&, const CoursePrecondtion&);
	private:
		static std::string generateId();
	protected:
		virtual bool precondtion(const Student&)const = 0;
		virtual std::ifstream& input(std::ifstream&)=0;
		virtual std::ostream& output(std::ostream&)const = 0;
	};

	std::ifstream& operator>>(std::ifstream&, CoursePrecondtion&);
	std::ostream& operator<<(std::ostream&, const CoursePrecondtion&);


	class CoursePassed :public CoursePrecondtion
	{
	protected:
		std::string courseId;
	public:
		CoursePassed() {};
		CoursePassed(std::string);
		CoursePassed(std::string, std::string);//id course id ucitavanje
		virtual std::string getType()const override;
		virtual std::string getInfo()const override;
	protected:
		virtual bool precondtion(const Student&)const override;
		virtual std::ifstream& input(std::ifstream&) override;
		virtual std::ostream& output(std::ostream&)const override;
	};

	class CoursePassedWithMinGrade :public CoursePrecondtion
	{
	private:
		std::string courseId;
		double minGrade;
	public:
		CoursePassedWithMinGrade() {};
		CoursePassedWithMinGrade(std::string, double);//course id minGrade
		CoursePassedWithMinGrade(std::string, std::string, double);//id course id minGrade
		virtual std::string getType()const override;
		virtual std::string getInfo()const override;
	protected:
		virtual bool precondtion(const Student&)const override;
		virtual std::ifstream& input(std::ifstream&)override;
		virtual std::ostream& output(std::ostream&)const override;


	};

	class NumberOfPassedCourse :public CoursePrecondtion
	{
	private:
		int num;
	public:
		NumberOfPassedCourse() {};
		NumberOfPassedCourse(int);
		NumberOfPassedCourse(std::string, int);
		virtual std::string getType()const override;
		virtual std::string getInfo()const override;
	protected:
		virtual bool precondtion(const Student&)const override;
		virtual std::ifstream& input(std::ifstream&)override;
		virtual std::ostream& output(std::ostream&)const override;
	};
	
	
}