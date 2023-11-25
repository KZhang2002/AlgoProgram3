#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<pair<int, pair<float,float>>> join(vector<pair<int, pair<float,float>>> vect1,
										  vector<pair<int, pair<float,float>>> vect2) {
	vector<pair<int, pair<float,float>>> sol;
	vector<pair<int, pair<float,float>>> applicants;
	applicants.insert(applicants.end(), vect1.begin(), vect1.end());
	applicants.insert(applicants.end(), vect2.begin(), vect2.end());

	for (int i = 0; i < applicants.size(); i++)
	{
		bool eligible = true;
		for (int j = 0; j < applicants.size(); j++)
		{
			if ((i != j) && (applicants[i].second.first < applicants[j].second.first) && (applicants[i].second.second > applicants[j].second.second))
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

vector<pair<int, pair<float,float>>> recursiveBestApplicants(vector<pair<int, pair<float,float>>>& applicants) {
	int length = applicants.size();

	if (length == 1) {
		return applicants;
	}

	vector<pair<int, pair<float, float>>> firstHalf(applicants.begin(), applicants.begin() + length / 2);
	vector<pair<int, pair<float, float>>> secondHalf(applicants.begin() + length/2, applicants.end());

	return join(recursiveBestApplicants(firstHalf), recursiveBestApplicants(secondHalf));
}

vector<int> BestApplicants(const vector<pair<float, float> >& applicants)
{
	vector<int> res;

	vector<pair<int, pair<float, float>>> eligibleApplicants;

	eligibleApplicants.reserve(applicants.size());
	for (int i = 0; i < applicants.size(); i++) {
		eligibleApplicants.emplace_back(i, applicants[i]);
	}

	eligibleApplicants = recursiveBestApplicants(eligibleApplicants);

	for (auto pair : eligibleApplicants) {
		res.push_back(pair.first);
	}

	return res;
}

