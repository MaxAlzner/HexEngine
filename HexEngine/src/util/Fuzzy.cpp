#include "..\main.h"

float FUZZY::NOT(float x)
{
	return Clamp(1.f - x);
}
float FUZZY::YES(float x)
{
	return Clamp(x);
}
float FUZZY::AND(float x, float y)
{
	return Clamp(x * y);
}
float FUZZY::OR(float x, float y)
{
	return Clamp(x + y);
}
float FUZZY::XOR(float x, float y)
{
	x = Clamp(x);
	y = Clamp(y);
	return (x * (1.f - y)) + ((1.f - x) * y);
}
float FUZZY::AND(int arguments, ...)
{
	va_list fVals;
	va_start(fVals, arguments);

	float result = float(va_arg(fVals, double));

	for (int i = 1; i < arguments; i++)
	{
		result = AND(result, float(va_arg(fVals, double)));
	}

	va_end(fVals);
	return result;
}
float FUZZY::OR(int arguments, ...)
{
	va_list fVals;
	va_start(fVals, arguments);

	float result = float(va_arg(fVals, double));

	for (int i = 1; i < arguments; i++)
	{
		result = OR(result, float(va_arg(fVals, double)));
	}

	va_end(fVals);
	return result;
}
float FUZZY::XOR(int arguments, ...)
{
	va_list fVals;
	va_start(fVals, arguments);

	float result = float(va_arg(fVals, double));

	for (int i = 1; i < arguments; i++)
	{
		result = XOR(result, float(va_arg(fVals, double)));
	}

	va_end(fVals);
	return result;
}

float FUZZY::isItMax(int x, int min, int max)
{
	if (x == min) return 0.f;
	if (x == max) return 1.f;
	if (x < min) return 0.f;
	else if (x > max) return 1.f;
	if (max < min || min > max) swap(min, max);

	return Clamp(float(x - min) / float(max - min));
}
float FUZZY::isItMin(int x, int min, int max)
{
	return 1.f - FUZZY::isItMax(x, min, max);
}
float FUZZY::isItHalf(int x, int min, int max)
{
	if (x == min) return 0.f;
	if (x == max) return 1.f;
	if (x < min) return 0.f;
	else if (x > max) return 1.f;
	if (max < min || min > max) swap(min, max);

	return Clamp((4.f * (x - min) * x - max) / ((max - min) * (min - max)));
}
float FUZZY::isItMax(float x, float min, float max)
{
	if (x == min) return 0.f;
	if (x == max) return 1.f;
	if (x < min) return 0.f;
	else if (x > max) return 1.f;
	if (max < min || min > max) swap(min, max);

	return Clamp(float(x - min) / float(max - min));
}
float FUZZY::isItMin(float x, float min, float max)
{
	return 1.f - FUZZY::isItMax(x, min, max);
}
float FUZZY::isItHalf(float x, float min, float max)
{
	if (x == min) return 0.f;
	if (x == max) return 1.f;
	if (x < min) return 0.f;
	else if (x > max) return 1.f;
	if (max < min || min > max) swap(min, max);

	return Clamp((4.f * (x - min) * x - max) / ((max - min) * (min - max)));
}
float FUZZY::isItMax(double x, double min, double max)
{
	if (x == min) return 0.f;
	if (x == max) return 1.f;
	if (x < min) return 0.f;
	else if (x > max) return 1.f;
	if (max < min || min > max) swap(min, max);

	return Clamp(float(x - min) / float(max - min));
}
float FUZZY::isItMin(double x, double min, double max)
{
	return 1.f - FUZZY::isItMax(x, min, max);
}
float FUZZY::isItHalf(double x, double min, double max)
{
	if (x == min) return 0.f;
	if (x == max) return 1.f;
	if (x < min) return 0.f;
	else if (x > max) return 1.f;
	if (max < min || min > max) swap(min, max);

	return Clamp(float((4.0 * (x - min) * x - max) / ((max - min) * (min - max))));
}
bool FUZZY::areEqual(float fVal1, float fVal2, float tolerance)
{
	if (fVal1 == fVal2) return true;
	if (tolerance < 0.f) tolerance = 0.f;
	float dif = fVal2 - fVal1;
	return (dif <= tolerance) && (dif >= tolerance * -1);
}

int FUZZY::defuzzify(float fVal, int min, int max)
{
	if (min == max) return min;
	return min + int(fVal * (max - min + 1.f));
}
float FUZZY::defuzzify(float fVal, float min, float max)
{
	if (min == max) return min;
	return min + float(fVal * (max - min));
}
double FUZZY::defuzzify(float fVal, double min, double max)
{
	if (min == max) return min;
	return min + double(fVal * (max - min));
}
bool FUZZY::defuzzify(float fVal, bool min, bool max)
{
	if (min == max) return min;
	if (fVal >= 0.5f) return max;
	else return min;
}

float FUZZY::distanceBetween(int size, float bMatrix1[], float bMatrix2[])
{
	float dist = 0.f;

	for (int i = 0; i < size; i++)
	{
		dist += (bMatrix2[i] - bMatrix1[i]) * (bMatrix2[i] - bMatrix1[i]);
	}

	return Clamp(sqrt(dist));
}
float FUZZY::distanceBetween(std::vector<float> bMatrix1, std::vector<float> bMatrix2)
{
	float dist = 0.f;

	for (unsigned i = 0; i < bMatrix1.size(); i++)
	{
		dist += (bMatrix2[i] - bMatrix1[i]) * (bMatrix2[i] - bMatrix1[i]);
	}

	return Clamp(sqrt(dist));
}
float FUZZY::isItClose(int size, float bMatrix1[], float bMatrix2[])
{
	float d = distanceBetween(size, bMatrix1, bMatrix2);
	float n = sqrt(float(size));

	return Clamp((n - d) / n);
}
float FUZZY::isItClose(std::vector<float> bMatrix1, std::vector<float> bMatrix2)
{
	float d = distanceBetween(bMatrix1, bMatrix2);
	float n = sqrt(float(bMatrix1.size()));

	return Clamp((n - d) / n);
}
float FUZZY::isItFar(int size, float bMatrix1[], float bMatrix2[])
{
	return 1.f - isItClose(size, bMatrix1, bMatrix2);
}
float FUZZY::isItFar(std::vector<float> bMatrix1, std::vector<float> bMatrix2)
{
	return 1.f - isItClose(bMatrix1, bMatrix2);
}
float FUZZY::computeBehavior(int numOfConditions, float conditions[], int numOfBehaviors, float behaviors[])
{
	if (numOfConditions < 1 || numOfBehaviors < 1) return -1.f;
	if (conditions == NULL || behaviors == NULL) return -1.f;

	float result = 0.f;
	for (int i = 0; i < numOfBehaviors; i++)
	{
		float row = conditions[0];
		if (!(i & 1)) row = NOT(row);

		for (int k = 1; k < numOfConditions; k++)
		{
			if (i & int(pow(2.f, k))) row = AND(row, YES(conditions[k]));
			else row = AND(row, NOT(conditions[k]));
		}
		result = OR(result, behaviors[i] * row);
	}
	return result;
}
float FUZZY::computeBehavior(std::vector<float> conditions, std::vector<float> behaviors)
{
	if (conditions.size() < 1 || behaviors.size() < 1) return -1.f;

	float result = 0.f;
	for (unsigned i = 0; i < behaviors.size(); i++)
	{
		float row = conditions[0];
		if (!(i & 1)) row = NOT(row);

		for (unsigned k = 1; k < conditions.size(); k++)
		{
			if (i & unsigned int(pow(2.f, float(k)))) row = AND(row, YES(conditions[k]));
			else row = AND(row, NOT(conditions[k]));
		}
		result = OR(result, behaviors[i] * row);
	}
	return result;
}

void FUZZY::adjustForError(std::vector<float> &conditions, std::vector<float> &behaviors, float error)
{
	if (error > 1.f) error = 1.f;
	else if (error < -1.f) error = -1.f;
	for (unsigned extremeCondition = 0; extremeCondition < conditions.size(); extremeCondition++)
	{
		float closeness = computeCloseness(extremeCondition, conditions);
		behaviors[extremeCondition] += error * closeness;
		behaviors[extremeCondition] = Clamp(behaviors[extremeCondition]);
	}
}
float FUZZY::computeDistance(std::vector<float> &bMatrix1, std::vector<float> &bMatrix2)
{
	float dist = 0.f;
	for (unsigned i = 0; i < bMatrix1.size(); i++) dist += (bMatrix2[i] - bMatrix1[i]) * (bMatrix2[i] - bMatrix1[i]);
	return Clamp(sqrt(dist));
}
float FUZZY::computeCloseness(int extremeCondition, std::vector<float> &conditions)
{
	std::vector<float>* extremeConditions = new std::vector<float>;
	for (unsigned i = 0; i < conditions.size(); i++) extremeConditions->push_back(0.f);
	computeExtremeCondition(extremeCondition, conditions);
	float result = computeCloseness(conditions, *extremeConditions);
	delete extremeConditions;
	return result;
}
float FUZZY::computeCloseness(std::vector<float> &bMatrix1, std::vector<float> &bMatrix2)
{
	float distance = computeDistance(bMatrix1, bMatrix2);
	return 1.f - (distance / sqrt(float(bMatrix1.size() & bMatrix2.size())));
}
void FUZZY::computeExtremeCondition(int extremeCondition, std::vector<float> &conditions)
{
	for (unsigned i = 0; i < conditions.size(); i++)
	{
		conditions[i] = ((extremeCondition & (1 << i)) > 0) ? 1.f : 0.f;
	}
}

STATEMACHINE::STATEMACHINE()
{
	this->currentNode = -1;
}
STATEMACHINE::~STATEMACHINE()
{
	this->nodes.clear();
	this->children.clear();
}

void STATEMACHINE::link(const char* thisNode, const char* thatNode, std::vector<float>* behaviors, TRAVERSENODES condition)
{
	int thisNodeIndex = this->findNode(thisNode);
	int thatNodeIndex = this->findNode(thatNode);

	if (thisNodeIndex < 0 || thatNodeIndex < 0) return;

	NODELINK link;
	link.next = thatNodeIndex;
	link.bevhaviors = behaviors;
	link.condition = condition;
	this->nodes[thisNodeIndex].links.push_back(link);
}
void STATEMACHINE::addNode(const char* name, INSIDENODE nodeFunction)
{
	int nodeIndex = this->findNode(name);
	if (nodeIndex >= 0) return;

	STATENODE node;
	node.name = name;
	node.function = nodeFunction;
	this->nodes.push_back(node);
}

void STATEMACHINE::step()
{
	if (this->nodes.size() < 1) return;
	if (this->currentNode < 0) this->currentNode = 0;

	STATENODE node = this->nodes[this->currentNode];
	float decision = 0;
	NODELINK link;
	for (unsigned i = 0; i < node.links.size(); i++)
	{
		link = node.links[i];
		float fVal = link.condition(*link.bevhaviors, node.name);
		if (fVal >= 0.5f && fVal > decision)
		{
			decision = fVal;
			this->currentNode = link.next;
		}
	}

	node.function();
}

int STATEMACHINE::findNode(const char* name)
{
	int index = -1;
	for (unsigned i = 0; i < this->nodes.size(); i++)
	{
		if (strcmp(name, this->nodes[i].name) == 0) index = i;
	}
	return index;
}