#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<pair<float,float>> join(vector<pair<float,float>> vect1,
										  vector<pair<float,float>> vect2) {
	vector<pair<float,float>> sol;
	vector<pair<float,float>> applicants;
	applicants.insert(applicants.end(), vect1.begin(), vect1.end());
	applicants.insert(applicants.end(), vect2.begin(), vect2.end());

	for (int i = 0; i < applicants.size(); i++)
	{
		bool eligible = true;
		for (int j = 0; j < applicants.size(); j++)
		{
			if ((i != j) && (applicants[i].first < applicants[j].first) && (applicants[i].second > applicants[j].second))
			{
				eligible = false;
				break;
			}
		}
		if (eligible)
			sol.push_back(applicants[i]);
	}

	return sol;
}

vector<pair<float,float>> recursiveBestApplicants(vector<pair<float,float>>& applicants) {
	int length = applicants.size();

	if (length == 1) {
		return applicants;
	}

	vector<pair<float,float>> firstHalf(applicants.begin(), applicants.begin() + length / 2);
	vector<pair<float,float>> secondHalf(applicants.begin() + length/2, applicants.end());

	return join(recursiveBestApplicants(firstHalf), recursiveBestApplicants(secondHalf));
}

vector<int> BestApplicants(const vector<pair<float, float> >& applicants)
{
	vector<int> res;

	vector<pair<float,float>> eligibleApplicants;

	eligibleApplicants = recursiveBestApplicants(eligibleApplicants);

	for (int i = 0; i < applicants.size(); i++) {
		res.push_back(i);
	}

	return res;
}

