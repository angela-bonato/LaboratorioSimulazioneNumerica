#include "lib9.h"

using namespace std;

vector<City> InitCircularCities(int N){
    //assumo la circonferenza con raggio 1. per semplicità, ergo io estraggo un angolo e x,y sono dati da suo cos e sin
    Random rand;
    InizRandom(rand);

    vector<City> vec;

    for(int i=0; i<N; i++){
        double theta=rand.Rannyu(0, 2*M_PI);
        
        City city;
        city.set_n(i);
        city.set_x(cos(theta));
        city.set_y(sin(theta));

        vec.push_back(city);
    }

    rand.SaveSeed();

    return vec;
}

vector<City> InitSquareCities(int N){
    //assumo il quadrato con lato 1. per semplicità
    Random rand;
    InizRandom(rand);

    vector<City> vec;

    for(int i=0; i<N; i++){
        double a=rand.Rannyu();
        double b=rand.Rannyu();
        
        City city;
        city.set_n(i);
        city.set_x(a);
        city.set_y(b);

        vec.push_back(city);
    }

    rand.SaveSeed();

    return vec;
}


void Swap(Path& path, int a, int b){
    int copy=path.get_ord(a);
    path.set_ord(a, path.get_ord(b));
    path.set_ord(b, copy);
}

vector<Path> InitRandomPop(Random& rand, int N, int P){
    vector<int> order;
    for(int i=0; i<N; i++) order.push_back(i);
    order.push_back(0);
    
    vector<Path> population;
    while(int(population.size())<P){
        Path path;
        path.set_Nc(N);

        if(int(population.size())==0) path.set_ord(order);
        else path.set_ord(population[population.size()-1].get_ord());

        for(int j=0; j<N/2; j++){
            int a=int(rand.Rannyu(1, N));
            int b=int(rand.Rannyu(1, N));
            while(a==b){
                b=int(rand.Rannyu(1, N));
            }
            Swap(path, a, b);
        }

        if(path.IsValid()) population.push_back(path); 
        else cerr << "Random invalid" << endl;
    }

    return population;
}

void CrossoverOperator(Random& rand, Path p1, Path p2, Path& s1, Path& s2, double pc){
    double r=rand.Rannyu();

    if(r<=pc){
        int l=p1.get_length()-1;

        int c=int(rand.Rannyu(1, l));
        vector<int> one, two;
        for(int i=0; i<c; i++){
            one.push_back(p1.get_ord(i));
            two.push_back(p2.get_ord(i));
        }

        for(int j=1; j<l; j++){
            for(int i=c; i<l; i++){
                if(p1.get_ord(i)==p2.get_ord(j)) one.push_back(p1.get_ord(i));
                if(p2.get_ord(i)==p1.get_ord(j)) two.push_back(p2.get_ord(i));
            }
        }

        one.push_back(0);
        two.push_back(0);
        s1.set_ord(one);
        s2.set_ord(two);

        if(!s1.IsValid() || !s2.IsValid()) cout << "Invalid crossover" << endl;
    }

    else{
        s1.set_ord(p1.get_ord());
        s2.set_ord(p2.get_ord());
    }
}

void MutationOperator(Random& rand, Path& path, double pm1, double pm2, double pm3, double pm4){
    //tutte le mutazioni devono preservare primo e ultimo elemento!
    int l=path.get_length()-1;

    double r1=rand.Rannyu();
    if(r1<=pm1){
        //prima mutazione: swap fra due elementi scelti a caso (escluso primo e ultimo)
        int a=int(rand.Rannyu(1, l));
        int b=int(rand.Rannyu(1, l));
        while(a==b) b=int(rand.Rannyu(1, l));
        Swap(path, a, b);
        if(!path.IsValid()) cout << "Mut1 invalid" << endl;
    }

    double r2=rand.Rannyu();
    if(r2<=pm2){
        //seconda mutazione: shifto in avanti i primi m elementi di n posti
        int m=int(rand.Rannyu(1, l));
        int n=int(rand.Rannyu(1, l));
        vector<int> one;
        vector<int> two;
        for(int i=1; i<=m; i++){
            one.push_back(path.get_ord(i));
        }
        for(int i=m+1; i<l; i++){
            two.push_back(path.get_ord(i));
        }

        for(int i=1; i<l; i++){
            int p=i+n;
            if(p>=l) p=n-(l-1-i);
            if(i<=m) {
                path.set_ord(p, one[i-1]);
            }
            if(i>m) {
                path.set_ord(p, two[i-1-m]);
            }
        }

        if(!path.IsValid()) cout << "Mut2 invalid" << endl;
    }

    double r3=rand.Rannyu();
    if(r3<=pm3){
        //terza mutazione: scambio m elementi contigui nella prima metà con m elementi contigui nella seconda metà
        int m=int(rand.Rannyu(1, l/2));
        int mid=l/2;
        for(int i=1; i<m; i++) Swap(path, i, mid+i);
        if(!path.IsValid()) cout << "Mut3 invalid" << endl;
    }

    double r4=rand.Rannyu();
    if(r4<=pm4){
        //quarta mutazione: inverto l'ordine di un gruppo di m elementi da una posizione n in poi
        int m=int(rand.Rannyu(1, l/2));
        int n=int(rand.Rannyu(1, l));
        for(int i=0; i<(m/2); i++){
            int left=i+n;
            if(left>=l) left=n-(l-1-i);
            int right=left+(m-i);
            if(right>=l) right-=(l-1);
            Swap(path, left, right);
        }

        if(!path.IsValid()) cout << "Mut4 invalid" << endl;
    }
}

bool ComparePaths(Path a, Path b){
    return a.get_loss() < b.get_loss();
}

void WriteBest(vector<Path> population, int s, ofstream& bout, ofstream& bhout){
    if(bout.is_open()) bout << scientific << population[0].get_loss() << endl;
    else cerr << "Errore: impossibile aprire bestloss.dat" << endl;

    double mean=0.0;
    for(int i=0; i<int(population.size())/2; i++){
        mean+=population[i].get_loss();
    }
    mean/=(double(population.size())/2.0);

    double stdev=0.0;
    for(int i=0; i<int(population.size())/2; i++){
        stdev+=(population[i].get_loss()-mean)*(population[i].get_loss()-mean);
    }
    stdev=sqrt(stdev/(double(population.size())/2.0));

    if(bhout.is_open()) bhout << scientific << mean << "  " << scientific << stdev << endl;
    else cerr << "Errore: impossibile aprire besthalfloss.dat" << endl;
}

vector<Path> ReplaceGeneration(Random& rand, vector<Path> old_population, vector<City> cities, int N, double pc, double pm1, double pm2, double pm3, double pm4, int s, ofstream& bout, ofstream& bhout, Path& best_path){
    int np=old_population.size();
    for(int i=0; i<np; i++) old_population[i].EvalLoss(cities);
    sort(old_population.begin(), old_population.end(), ComparePaths);   //ordino la popolazione in modo che l'indice più basso sia quello del path con loss più bassa

    WriteBest(old_population, s, bout, bhout);
    if(old_population[0].get_loss() < best_path.get_loss()) best_path=old_population[0];

    vector<Path> new_population;
    while(int(new_population.size())<=np-2){
        //a questo punto sfrutto l'ordinamento per estrarre con la probabilità desiderata
        double r1=rand.Rannyu();
        int e1=int(np*pow(r1, 5));
        double r2=rand.Rannyu();
        int e2=int(np*pow(r2, 5));
        while(e2==e1){
            r2=rand.Rannyu();
            e2=int(np*pow(r2, 5));
        }

        Path son1, son2;
        son1.set_Nc(N);
        son2.set_Nc(N);
        CrossoverOperator(rand, old_population[e1], old_population[e2], son1, son2, pc);
        MutationOperator(rand, son1, pm1, pm2, pm3, pm4);
        MutationOperator(rand, son2, pm1, pm2, pm3, pm4);

        if(son1.IsValid() && son2.IsValid()){
            new_population.push_back(son1);
            new_population.push_back(son2); 
        } 
    }

    return new_population;
}

void TravSalesProb(vector<City> cities,int N, int P, int S, double pc, double pm1, double pm2, double pm3, double pm4, ofstream& bout, ofstream& bhout, ofstream& pout){
    Random rand;   
    InizRandom(rand);
    vector<Path> starting_population=InitRandomPop(rand, cities.size(), P);
    vector<Path> new_population;
    Path best_path=starting_population[0];
    best_path.EvalLoss(cities);

    for(int s=0; s<S; s++){
        new_population=ReplaceGeneration(rand, starting_population, cities, N, pc, pm1, pm2, pm3, pm4, s, bout, bhout, best_path);
        starting_population=new_population;
        cout << "Rimpiazzata popolazione " << s << endl;
    }

    if(pout.is_open()){
        pout << "#" << scientific << best_path.get_loss() << endl;
        for(int i=0; i<int(best_path.get_ord().size()); i++){
            pout <<  scientific << cities[best_path.get_ord(i)].get_x() << "  " << scientific << cities[best_path.get_ord(i)].get_y() <<  endl;
        }
    }
    else cerr << "Errore: impossibile aprire bestpath.dat" << endl;

    rand.SaveSeed();
}
