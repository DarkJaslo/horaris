#ifndef App_hh
#define App_hh

#include <qwidget.h>
#include <QListWidget>
#include <string>
#include <vector>
#include <set>
#include "HTTPSGetter.hh"
#include "Parser.hh"
#include "Data.hh"
#include "MyComboBox.hh"

class App : public QWidget
{
 Q_OBJECT

public:

  App(QWidget *parent = 0);
  //Gets both semesters for this year
  void getSemesters();
  //Gets the data into FIB_DATA.txt
  void getData();
  void receiveListWidget(QListWidget* list);
  void receiveStudiesBox(MyComboBox* box);

public slots:
  void setMajor(const QString& m);
  void setSemester(const QString& s);
  void setScheduleSize(int size);
  void setMixGroups(bool mix);
  void setSchedulePreference(const QString& pref);
  void addSubject(const QString& subj);
  void removeSubject(const QString& subj);
  void addSubjectAlways(const QString& subj);
  void removeSubjectAlways(const QString& subj);
  void excludeGroup(const QString& subjGr);
  void unExcludeGroup(const QString& subjGr);
  void setFilter(const QString& filter);
  void generate();

signals:
  void writtenSchedules();
  void closeApp();
  void loadSemester(const QString& s);
  void changedSemester();
  void loadMajor(const QString& m);

private:

//Parses data
void parseData(int index, const std::string& filename);

void computeSchedules();

void initList();
void initList(const std::string& filter);

void sortList();

void getDataTask(int semest);

void initStudiesBox();


int semester;
std::string       semesters[2];
std::string       major;
std::vector<std::vector<std::string>> majors;
std::string       filter;

const std::string url = "https://api.fib.upc.edu";
const std::string path1 = "/v2/quadrimestres/";
const std::string path2 = "/classes/?format=api&client_id=liSPe2KsaYUovErkk1WyqgMdYxOD1Wqd3VCXwhoy";

const std::string pathSemesters = "/v2/quadrimestres/actual/?format=api&client_id=liSPe2KsaYUovErkk1WyqgMdYxOD1Wqd3VCXwhoy";
const std::string pathStudies = "";

int dataIndex;
std::vector<jaslo::Data>  data;
int     sizeHorari;
bool    mixGroups;
jaslo::SchedulePreference preference;
const static int   maxPrintedSchedules = 1000;
std::fstream outputFile;
const std::string outputFilename = "OUTPUT_SCHEDULES.txt"; 

std::set<std::string> mustAppearSubjects;
std::set<std::string> otherSubjects;
std::set<std::pair<std::string,int>> groupsToExclude;
QListWidget* list;
MyComboBox* studiesBox;

std::vector<std::vector<std::string>> allSubjectNames;

std::vector<std::map<std::string,std::vector<std::string>>> allSubjectNamesByMajor;
};

#endif