#include<bits/stdc++.h>
using namespace std;

class Chromosome {
public:
    string gene;
	int fitness;
};

struct Population {
	vector<Chromosome> Chromosomes = vector<Chromosome>(15);
}Pop;

int prime[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int modulo[7]={67,136,1056,10453,234679,3289730,12385934};
unsigned int RSHash(const char* str, unsigned int length)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}
unsigned int PJWHash(const char* str, unsigned int length)
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          =
                      (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash = 0;
   unsigned int test = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << OneEighth) + (*str);

      if ((test = hash & HighBits) != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int x    = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << 4) + (*str);

      if ((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }

      hash &= ~x;
   }

   return hash;
}
unsigned int BKDRHash(const char* str, unsigned int length)
{
   unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash * seed) + (*str);
   }

   return hash;
}
unsigned int SDBMHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}
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
    vector <unsigned int> hashed_seed;
    hash <string> hash_fn; //only required if secondhashed
    int total_number;
    cout<<"enter the number random numbers that you require";
    cin>>total_number;
   while(total_number>0)
    {srand(time(NULL));
    string seed;
    seed=get_seed();
	bool Validity = false;
	int gamma_rays = 500,iteration = 0;
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
				int crossover2 = rand() % Parents.size()
				Pop.Chromosomes.at(i).gene.at(j) = Pop.Chromosomes.at(crossover).gene.at(j);
				if (rand() % 1000 < gamma_rays) { Pop.Chromosomes.at(i).gene.at(j) = (unsigned char)rand() % 96 + 32; }
			}
		}
    int random1=rand()%7;
    { f<<(APHash((Pop.Chromosomes.at(random1).gene).c_str(),Pop.Chromosomes.at(random1).gene.length()))%(modulo[random1])<<"\n";
    f<<(hash_fn(Pop.Chromosomes.at(random1).gene))%(modulo[random1])<<"\n";
    f<<(DEKHash((Pop.Chromosomes.at(random1).gene).c_str(),Pop.Chromosomes.at(random1).gene.length()))%(modulo[random1])<<"\n";
    f<<(DJBHash((Pop.Chromosomes.at(random1).gene).c_str(),Pop.Chromosomes.at(random1).gene.length()))%(modulo[random1])<<"\n";
    f<<(RSHash((Pop.Chromosomes.at(random1).gene).c_str(),Pop.Chromosomes.at(random1).gene.length()))%(modulo[random1])<<"\n";
    f<<(JSHash((Pop.Chromosomes.at(random1).gene).c_str(),Pop.Chromosomes.at(random1).gene.length()))%(modulo[random1])<<"\n";
    f<<(PJWHash((Pop.Chromosomes.at(random1).gene).c_str(),Pop.Chromosomes.at(random1).gene.length()))%(modulo[random1])<<"\n";
    f<<(ELFHash((Pop.Chromosomes.at(random1).gene).c_str(),Pop.Chromosomes.at(random1).gene.length()))%(modulo[random1])<<"\n";
    f<<(SDBMHash((Pop.Chromosomes.at(random1).gene).c_str(),Pop.Chromosomes.at(random1).gene.length()))%(modulo[random1])<<"\n";
    f<<(BKDRHash((Pop.Chromosomes.at(random1).gene).c_str(),Pop.Chromosomes.at(random1).gene.length()))%(modulo[random1])<<"\n";
    total_number-=10;
    }
	}
    }
	return 0;
}


