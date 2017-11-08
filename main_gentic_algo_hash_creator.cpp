#include<bits/stdc++.h>
using namespace std;

class Chromosome {
public:
    string gene;
	int fitness;
};

struct Population {
	vector<Chromosome> Chromosomes = vector<Chromosome>(500);
}Pop;

int prime[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

unsigned int DEKHash(const char* str, unsigned int length)
{
   unsigned int hash_ = length;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash_ = ((hash_ << 5) ^ (hash_ >> 27)) ^ (*str);
   }

   return hash_;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
   unsigned int hash_ = 5381;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash_ = ((hash_ << 5) + hash_) + (*str);
   }

   return hash_;
}

unsigned int APHash(const char* str, unsigned int length)
{
   unsigned int hash_ = 0xAAAAAAAA;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash_ ^= ((i & 1) == 0) ? (  (hash_ <<  7) ^ (*str) * (hash_ >> 3)) :
                               (~((hash_ << 11) + ((*str) ^ (hash_ >> 5))));
   }

   return hash_;
}
string get_seed()
{   srand(time(NULL));
    ifstream f("file.txt");
    f.seekg(rand()%100000);
    char ch;
    string seed;
    for(int i=0;i<100;i++)
    {
        f.get(ch);
        seed+=ch;
    }

    return seed;
}

int main() {
     ofstream f("random.txt",ios_base::app);
    unsigned int hashed_seed_1,hashed_seed_2,hashed_seed_3,hashed_seed_4;
    hash <string> hash_fn; //only required if secondhashed
    int total_number;
    cout<<"enter the number random numbers that you require";
    cin>>total_number;
   while(total_number>0)
    {srand(time(NULL));
    string seed;
    seed=get_seed();
	bool Validity = false;
	int gamma_rays = 50,iteration = 0;
	for (int i = 0; i < Pop.Chromosomes.size(); i++) {
		Pop.Chromosomes.at(i).gene.resize(seed.size());
		for (int j = 0; j < seed.size(); j++) { Pop.Chromosomes.at(i).gene.at(j) = (char)rand() % 96 + 32; }
		Pop.Chromosomes.at(i).fitness = 0;
	}
	int choose_prime=prime[rand()%25];
	while (iteration<choose_prime) {
		iteration++;
		for (int i = 0; i < Pop.Chromosomes.size(); i++) {
			Pop.Chromosomes.at(i).fitness = 0;
			for (int j = 0; j < Pop.Chromosomes.at(i).gene.size(); j++)
                { if (Pop.Chromosomes.at(i).gene.at(j) == seed.at(j))
                    { Pop.Chromosomes.at(i).fitness += 8;
                    }
                }
			if (Pop.Chromosomes.at(i).fitness == seed.size() * 8) Validity = true;
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
    if(total_number>0)
    {hashed_seed_1=(APHash((Parents.at(0).gene).c_str(),Parents.at(0).gene.length()));
    hashed_seed_2=(hash_fn(Parents.at(0).gene));
    hashed_seed_3=(DEKHash((Parents.at(0).gene).c_str(),Parents.at(0).gene.length()));
    hashed_seed_4=(DJBHash((Parents.at(0).gene).c_str(),Parents.at(0).gene.length()));
    f<<hashed_seed_1+hashed_seed_2+hashed_seed_3+hashed_seed_4<<'\n';
    cout<<total_number<<"\t:"<<hashed_seed_1+hashed_seed_2+hashed_seed_3+hashed_seed_4<<'\n';
    --total_number;
    }
	}
    }
	return 0;
}

