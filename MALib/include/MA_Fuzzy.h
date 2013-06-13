#ifndef _MA_FUZZY_H_
#define _MA_FUZZY_H_

class FUZZY
{
public:
	static float NOT(float x);
	static float YES(float x);
	static float AND(float x, float y);
	static float OR(float x, float y);
	static float XOR(float x, float y);
	static float AND(int arguments, ...);
	static float OR(int arguments, ...);
	static float XOR(int arguments, ...);

	static float isItMax(int x, int min, int max);
	static float isItMin(int x, int min, int max);
	static float isItHalf(int x, int min, int max);
	static float isItMax(float x, float min, float max);
	static float isItMin(float x, float min, float max);
	static float isItHalf(float x, float min, float max);
	static float isItMax(double x, double min, double max);
	static float isItMin(double x, double min, double max);
	static float isItHalf(double x, double min, double max);
	static bool areEqual(float fVal1, float fVal2, float tolerance = 0.001f);

	static int defuzzify(float fVal, int min, int max);
	static float defuzzify(float fVal, float min, float max);
	static double defuzzify(float fVal, double min, double max);
	static bool defuzzify(float fVal, bool min, bool max);

	static float distanceBetween(int size, float bMatrix1[], float bMatrix2[]);
	static float distanceBetween(std::vector<float> bMatrix1, std::vector<float> bMatrix2);
	static float isItClose(int size, float bMatrix1[], float bMatrix2[]);
	static float isItClose(std::vector<float> bMatrix1, std::vector<float> bMatrix2);
	static float isItFar(int size, float bMatrix1[], float bMatrix2[]);
	static float isItFar(std::vector<float> bMatrix1, std::vector<float> bMatrix2);
	static float computeBehavior(int numOfConditions, float conditions[], int numOfBehaviors, float behaviors[]);
	static float computeBehavior(std::vector<float> conditions, std::vector<float> behaviors);

	static void adjustForError(std::vector<float> &conditions, std::vector<float> &behaviors, float error);
	static float computeDistance(std::vector<float> &bMatrix1, std::vector<float> &bMatrix2);
	static float computeCloseness(int extremeCondition, std::vector<float> &conditions);
	static float computeCloseness(std::vector<float> &bMatrix1, std::vector<float> &bMatrix2);
	static void computeExtremeCondition(int extremeCondition, std::vector<float> &conditions);
};

typedef float (*TRAVERSENODES)(std::vector<float> behaviors, const char* nodeName);
typedef void (*INSIDENODE)();
struct NODELINK
{
	std::vector<float>* bevhaviors;
	TRAVERSENODES condition;
	int next;
};
struct STATENODE
{
	const char* name;
	std::vector<NODELINK> links;
	INSIDENODE function;
};
class STATEMACHINE
{
public:
	STATEMACHINE();
	~STATEMACHINE();

	void link(const char* thisNode, const char* thatNode, std::vector<float>* behaviors, TRAVERSENODES condition);
	void addNode(const char* name, INSIDENODE nodeFunction);

	void step();
private:
	std::vector<STATENODE> nodes;
	std::vector<STATEMACHINE*> children;
	int currentNode;

	int findNode(const char* name);
};

#endif