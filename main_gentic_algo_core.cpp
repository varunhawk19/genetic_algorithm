#include<bits/stdc++.h>
using namespace std;
class Chromosome {
public:
    string gene;
	int fitness;
};
struct Population {
	vector<Chromosome> Chromosomes = vector<Chromosome>(50000);
}Pop;
int main() {
	string search_token = "this is written by vHAWK";
	bool Validity = false;
	int gamma_rays = 25,iteration = 0;
	srand(time(NULL));
	for (int i = 0; i < Pop.Chromosomes.size(); i++) {
		Pop.Chromosomes.at(i).gene.resize(search_token.size());
		for (int j = 0; j < search_token.size(); j++) { Pop.Chromosomes.at(i).gene.at(j) = (char)rand() % 96 + 32; }
		Pop.Chromosomes.at(i).fitness = 0;
	}
	while (!Validity) {
		iteration++;
		for (int i = 0; i < Pop.Chromosomes.size(); i++) {
			Pop.Chromosomes.at(i).fitness = 0;
			for (int j = 0; j < Pop.Chromosomes.at(i).gene.size(); j++)
                { if (Pop.Chromosomes.at(i).gene.at(j) == search_token.at(j))
                    { Pop.Chromosomes.at(i).fitness += 8;
                    }
                }
			if (Pop.Chromosomes.at(i).fitness == search_token.size() * 8) Validity = true;
		}

		sort(Pop.Chromosomes.begin(), Pop.Chromosomes.end(), [](Chromosome const &a, Chromosome &b) {return a.fitness > b.fitness; });
		vector<Chromosome> Parents{ Pop.Chromosomes.at(0), Pop.Chromosomes.at(1) };
		for (int i = 0; i < Pop.Chromosomes.size(); i++) {
			for (int j = 0; j < Pop.Chromosomes.at(i).gene.size(); j++) {
				int crossover = rand() % Parents.size();
				Pop.Chromosomes.at(i).gene.at(j) = Parents.at(crossover).gene.at(j);
				if (rand() % 1000 < gamma_rays) { Pop.Chromosomes.at(i).gene.at(j) = (unsigned char)rand() % 96 + 32; }
			}
		}
    cout << "Generation : " << iteration << " Highest fitness : " << Parents.at(0).fitness << " With Sequence : " << Parents.at(0).gene.c_str() << endl;
	}
	cout << "Generation " << iteration << " Evolved to the full sequence" << endl;
	return 0;
}

