#include <iostream>
using namespace std;

#define MAXREQDSKILLS 5
#define MAXSPORTSINTEREST 5
#define MAXLEARNERS 5

static int countVar = 0;
static int countVar1 = 0;
static int countVar2 = 0;

class Mentor;

class Student
{
private:
    string studentID;
    string studentName;
    int age;
    string sportsInterests[MAXSPORTSINTEREST];
    Mentor *mentorAssigned;

public:
    Student(string id, string name, int age)
    {
        studentID = id;
        studentName = name;
        this->age = age;
        mentorAssigned = nullptr;
    }

    string getStudentID() { return studentID; }
    string getStudentName() { return studentName; }
    int getAge() { return age; }

    void registerForMentorship(Mentor &m);
    void viewMentorDetails();

    void updateSportsInterest(string sport)
    {
        if (countVar2 < MAXSPORTSINTEREST)
        {
            sportsInterests[countVar2++] = sport;
        }
    }
};

class Mentor
{
private:
    string mentorName;
    string mentorID;
    string sportsExpertise[5];
    int maxLearners;
    string assignedLearners[MAXLEARNERS];

public:
    Mentor(string name, string id, int maxL)
    {
        mentorName = name;
        mentorID = id;
        maxLearners = maxL;
        countVar1 = 0;
    }

    string getMentorName() { return mentorName; }
    string getMentorID() { return mentorID; }
    string *getMentorSportsExpertise() { return sportsExpertise; }

    void assignLearner(Student &s)
    {
        if (countVar1 < maxLearners)
        {
            assignedLearners[countVar1++] = s.getStudentID();
            cout << "Student " << s.getStudentID() << " assigned to mentor " << mentorName << endl;
        }
        else
        {
            cout << "Mentor " << mentorName << " has reached max learners.\n";
        }
    }

    void removeLearner(Student &s)
    {
        for (int i = 0; i < countVar1; i++)
        {
            if (assignedLearners[i] == s.getStudentID())
            {
                assignedLearners[i] = assignedLearners[--countVar1];
                cout << "Student " << s.getStudentID() << " removed from mentor " << mentorName << endl;
                return;
            }
        }
        cout << "Student not found in assigned learners.\n";
    }

    void viewLearners()
    {
        cout << "Mentor " << mentorName << "'s Learners:\n";
        for (int i = 0; i < countVar1; i++)
        {
            cout << "- " << assignedLearners[i] << endl;
        }
    }

    void provideGuidance()
    {
        cout << "Guidance will be provided after evaluating performance.\n";
    }
};

void Student::registerForMentorship(Mentor &m)
{
    if (mentorAssigned == nullptr)
    {
        mentorAssigned = &m;
        m.assignLearner(*this);
    }
    else
    {
        cout << "Student " << studentName << " is already assigned a mentor.\n";
    }
}

void Student::viewMentorDetails()
{
    if (mentorAssigned != nullptr)
    {
        cout << "Mentor Name: " << mentorAssigned->getMentorName() << "\n";
        cout << "Mentor ID: " << mentorAssigned->getMentorID() << "\n";
    }
    else
    {
        cout << "No mentor assigned.\n";
    }
}

class Skill
{
private:
    string skillID;
    string skillName;
    string skillDescription;

public:
    Skill(string id, string name, string desc)
    {
        skillID = id;
        skillName = name;
        skillDescription = desc;
    }

    string getSkillID() { return skillID; }
    string getSkillName() { return skillName; }
    string getSkillDescription() { return skillDescription; }

    void showSkillDetails()
    {
        cout << "Skill ID: " << skillID << "\n";
        cout << "Skill Name: " << skillName << "\n";
        cout << "Description: " << skillDescription << "\n";
    }

    void updateDescription(string newDescription)
    {
        skillDescription = newDescription;
    }
};

class Sports
{
public:
    string sportsID;
    string sportsName;
    string description;
    string requiredSkills[MAXREQDSKILLS];

    Sports(string id, string name, string desc)
    {
        sportsID = id;
        sportsName = name;
        description = desc;
        countVar = 0;
    }

    void addSkill(Skill &s)
    {
        if (countVar < MAXREQDSKILLS)
        {
            requiredSkills[countVar++] = s.getSkillName();
        }
    }

    void removeSkill(Skill &s)
    {
        for (int i = 0; i < countVar; i++)
        {
            if (s.getSkillName() == requiredSkills[i])
            {
                requiredSkills[i] = requiredSkills[--countVar];
                return;
            }
        }
    }
};

int main()
{

    Mentor m1("John miller", "M321", 2);
    Mentor m2("Jane jason", "M654", 1);

    Student s1("S001", "Franklin", 20);
    Student s2("S002", "Chris", 21);
    Student s3("S003", "Lemar", 19);

    cout << "\nRegistering students for mentorship:\n";
    s1.registerForMentorship(m1);
    s2.registerForMentorship(m1);
    s3.registerForMentorship(m1);

    cout << "\nViewing mentor details for students:\n";
    s1.viewMentorDetails();
    s2.viewMentorDetails();
    s3.viewMentorDetails();

    cout << "\nViewing learners assigned to Mentor 1:\n";
    m1.viewLearners();

    cout << "\nRemoving student from mentorship:\n";
    m1.removeLearner(s1);
    m1.viewLearners();

    cout << "\nRegistering removed student to another mentor:\n";
    s1.registerForMentorship(m2);
    m2.viewLearners();

    cout << "\nProviding guidance:\n";
    m1.provideGuidance();
    m2.provideGuidance();

    Skill skill1("SK001", "Ball Control", "Mastering ball control while maneuvering through defenders.");
    Skill skill2("SK002", "Goal Scoring", "Accurately aiming and striking the ball to score goals");

    cout << "\nSkill details:\n";
    skill1.showSkillDetails();
    skill2.showSkillDetails();

    cout << "\nUpdating skill:\n";
    skill1.updateDescription(" ball control Improved.");
    skill1.showSkillDetails();

    Sports football("SP001", "Soccer", "A popular team sport played with a round ball and goals at each end.");

    cout << "\nAdding skills to Soccer:\n";
    football.addSkill(skill1);
    football.addSkill(skill2);

    cout << "\nRemoving a skill from Soccer:\n";
    football.removeSkill(skill1);

    return 0;
}