#include <iostream>
#include <iomanip>
#include <strings.h>

#define DISCOUNT 1
#define SIZE 5
#define NOISE_PROB 0.03


//int Decisions_Remaining=100;
class state_t {
    bool grid_[SIZE][SIZE];   

  public:
    state_t()
   {
       for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
               grid_[i][j]=0;
            }
        }

         grid_[0][0]=1;
         grid_[0][3]=1;
         grid_[0][4]=1;
         grid_[1][0]=1;
         grid_[1][4]=1;
         grid_[2][0]=1;
         grid_[2][1]=1;
         grid_[2][3]=1;
         grid_[3][1]=1;
         grid_[3][3]=1;
         grid_[4][2]=1;
         grid_[4][3]=1;

    }
    state_t(const state_t &s)
     {
           for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++)
                  grid_[i][j]=s.grid_[i][j];  
        

      }

    ~state_t() { }

    size_t hash() const {
        return (grid_[0][0] + (grid_[0][1] << 1) + (grid_[0][2] << 2) + (grid_[0][3] << 3) + (grid_[0][4] << 4) + (grid_[1][0] << 5) + (grid_[1][1] << 6) + (grid_[1][2] << 7) + (grid_[1][3] << 8) + (grid_[1][4] << 9) + (grid_[2][0] << 10) + (grid_[2][1] << 11) + (grid_[2][2] << 12) + (grid_[2][3] << 13) + (grid_[2][4] << 14) + (grid_[3][0] << 15) + (grid_[3][1] << 16) + (grid_[3][2] << 17) + (grid_[3][3] << 18) + (grid_[3][4] << 19) + (grid_[4][0] << 20) + (grid_[4][1] << 21) + (grid_[4][2] << 22) + (grid_[4][3] << 23) + (grid_[4][4] << 24));
    }

  
   
    

    

    const state_t& operator=( const state_t &s) {
       
        for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++)
                  grid_[i][j]=s.grid_[i][j]; 
        return *this;
    }
    bool operator==(const state_t &s) const {
        
        
        for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++)
                    if(grid_[i][j]!=s.grid_[i][j])
                        return 0;

                    
            
       
       return  1;
    }

    bool operator!=(const state_t &s) const {

       for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++)
                    if(grid_[i][j]!=s.grid_[i][j])
                        return 1;
        return 0;
        
    }
    bool operator<(const state_t &s) const {
        for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++)
                    if(grid_[i][j]<s.grid_[i][j])
                        return true;
                    else if (grid_[i][j]>s.grid_[i][j])
                        return false;
       return false;
       
    }
     void print(std::ostream &os) const {
        os << "(" ;
          for(int i=0;i<SIZE;i++)
          {
                for(int j=0;j<SIZE;j++)
                {
                    os<<grid_[i][j]<<" ";
                }
                os<<"\n";
         }
            os<<")";
    }
    friend class problem_t;
};

inline std::ostream& operator<<(std::ostream &os, const state_t &s) {
    s.print(os);
    return os;
}

class problem_t : public Problem::problem_t<state_t> {
   
    //float costs_[5];
    state_t init_;
    state_t goal_;
    float Noise_[SIZE][SIZE];
    //static const bool default_connections_[];
    //static const float default_wind_transition_[];
    //static const float default_costs_[];

  public:
    problem_t(int dim1, int dim2)
      : Problem::problem_t<state_t>(DISCOUNT)
          {
        //bcopy(default_Noise_, Noise_, SIZE*SIZE* sizeof(float));
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                init_.grid_[i][j]=0;
		      Noise_[i][j]=NOISE_PROB;
            }
        }
         

         init_.grid_[0][0]=1;
         init_.grid_[0][3]=1;
         init_.grid_[0][4]=1;
         init_.grid_[1][0]=1;
         init_.grid_[1][4]=1;
         init_.grid_[2][0]=1;
         init_.grid_[2][1]=1;
         init_.grid_[2][3]=1;
         init_.grid_[3][1]=1;
         init_.grid_[3][3]=1;
         init_.grid_[4][2]=1;
         init_.grid_[4][3]=1;
            //connections_[NUM_COMPUTERS-1]=1;
            //connections_[NUM_COMPUTERS*(NUM_COMPUTERS-1)]=1;

      
    }
    virtual ~problem_t() { }

    virtual Problem::action_t number_actions(const state_t &s) const { return SIZE*SIZE;}
    
    virtual const state_t& init() const { return init_; }
    virtual bool terminal(const state_t &s) const {

        return (false);
    }
    virtual bool dead_end(const state_t &s) const { return false; }
    virtual bool applicable(const state_t &s, ::Problem::action_t a) const {
        return true;
        if(a!=SIZE*SIZE)
        {    
            return (!s.grid_[a/SIZE][a%SIZE]);
        }
        else
        {    

            for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++)
                {
                    if(s.grid_[i][j]==0)
                        return false;
                }
        }        
        return true;
    }
    virtual float cost(const state_t &s, Problem::action_t a) const {
        float reward=0;

        //std::vector<std::pair<state_t,float> > outcomes;
        
        //reward=(a==0)?0:-REBOOT_PENALTY;
        reward+=cells_alive(s);
        //next(s,a,outcomes);
        /*for(unsigned i=0;i<outcomes.size();i++)
        {
            reward+=outcomes[i].second*working_comps(outcomes[i].first);
        }*/
          
       return -1*reward;
       // return terminal(s) ? 0 : -1*reward;
    }
    virtual unsigned alive_nbrs(const state_t &s, int x, int y) const{
        unsigned count=0;
        for(int i=-1;i<=1;i++)
            for(int j=-1;j<=1;j++)
            {
                if(i==0 && j==0)
                    continue;
                if((i+x>=0)&&(i+x<SIZE)&&(j+y>=0)&&(j+y<SIZE))
                    count+=s.grid_[i+x][j+y];

            }
        return count;
    }
     virtual unsigned cells_alive( const state_t &s) const{
        unsigned count=0;
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                if(s.grid_[i][j])
                    count+=1;
            }
        }    
        return count;

    }

    virtual void sample_factored(const state_t &s, Problem::action_t a, state_t &outcome) const {
        float p=1;
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                float m;
                int living_nbrs=alive_nbrs(s,i,j);
                if((a==i*SIZE+j)||(s.grid_[i][j]&&((living_nbrs==2)||(living_nbrs==3)))||((s.grid_[i][j]==0)&&(living_nbrs==3)))
                {
                    m=(1-Noise_[i][j]);
                }
                else
                    m=Noise_[i][j];
                float r=Random::real();
                if(r<m)
                    outcome.grid_[i][j]=1;
                else
                    outcome.grid_[i][j]=0;
            }
        }
       
    }





    virtual void next(const state_t &s, Problem::action_t a, std::vector<std::pair<state_t,float> > &outcomes) const {
      /*  ++expansions_;
       outcomes.clear();
       outcomes.reserve(NUM_COMPUTERS);
       state_t next_s;
       float p;
       if(a!=i)

       for(int i=0;i<NUM_COMPUTERS;i++)
       {

       }*/


       /*
         outcomes.clear();
        outcomes.reserve(pow(2,NUM_COMPUTERS));
        state_t next_s;
        float p;
        for(int i=0;i<(pow(2,NUM_COMPUTERS));i++)
        {
            for(int j=0;j<NUM_COMPUTERS;j++)
            {
                next_s.computer_state_[j]=(((1<<j)&i)&&1);
            }
            p=calculate_transition(s,next_s,a);
            if(p>1)
            {
                std::cout<<"error here";
                exit(0);
            }
            if(p>0)
            {
                outcomes.push_back(std::make_pair(next_s, p));
            }
        }*/
         
    }
    virtual void print(std::ostream &os) const { }
};

 

//const bool problem_t::default_connections_[] = {0
    
   /* 1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1

*/

   /* 1,1,1,1,1,1,1,1,1,1,
    1,1,0,0,0,0,0,0,0,0,
    1,0,1,0,0,0,0,0,0,0,
    1,0,0,1,0,0,0,0,0,0,
    1,0,0,0,1,0,0,0,0,0,
    1,0,0,0,0,1,0,0,0,0,
    1,0,0,0,0,0,1,0,0,0,
    1,0,0,0,0,0,0,1,0,0,
    1,0,0,0,0,0,0,0,1,0,
    1,0,0,0,0,0,0,0,0,1*/

/*    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0*/
 /*   1,0,0,0,1,0,0,0,0,1,
    1,1,0,0,0,0,1,1,0,0,
    0,0,1,1,0,0,1,0,0,0,
    0,0,1,1,1,1,0,0,0,0,
    1,1,0,0,1,0,0,1,0,0,
    0,0,1,0,0,1,1,0,0,1,
    0,1,0,0,0,0,1,1,1,0,
    1,0,0,1,1,0,0,1,0,0,
    0,1,0,0,1,1,0,0,1,0,
    0,1,0,1,0,0,0,1,0,1

*/
   /* 1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1*/

// 1,1,1,1,1,
// 1,1,1,1,1,
// 1,1,1,1,1,
// 1,1,1,1,1,
// 1,1,1,1,1
   /*
   1,1,0,0,0,
   1,1,0,0,0,
   0,0,1,0,0,
   0,0,0,1,0,
   0,0,0,0,1*/


/*1,0,0,1,0,
0,1,0,0,0,
0,0,1,1,0,
0,0,0,1,1,
0,0,0,0,1
  */
/*  	1,0,0,1,0,0,0,0,
    0,1,0,0,0,0,0,1,
    0,0,1,1,0,0,0,0,
    0,0,0,1,1,0,0,0,
    0,0,0,0,1,0,1,0,
    0,0,0,1,0,1,0,1,
    0,0,0,0,0,0,1,0,
    0,0,0,0,0,1,0,1 */
/*
    1,1,0,0,0,0,0,0,0,0,
    0,1,1,0,0,0,0,0,0,0,
    0,0,1,1,0,0,0,0,0,0,
    0,0,0,1,1,0,0,0,0,0,
    0,0,0,0,1,1,0,0,0,0,
    0,0,0,0,0,1,1,0,0,0,
    0,0,0,0,0,0,1,1,0,0,
    0,0,0,0,0,0,0,1,1,0,
    0,0,0,0,0,0,0,0,1,1,
    1,0,0,0,0,0,0,0,0,1,

*/
  /*  1,0,0,1,0,0,0,0,1,0,
    0,1,0,0,0,0,0,1,0,0,
    0,0,1,1,0,0,0,0,1,0,
    0,0,0,1,1,0,0,0,0,0,
    0,0,0,0,1,0,1,0,0,0,
    0,0,0,1,0,1,0,1,0,0,
    0,0,0,0,0,0,1,0,1,0,
    0,0,0,0,0,1,0,1,0,1,
    0,0,0,0,0,1,0,0,1,0,
    0,1,0,0,0,0,0,0,0,1*/

//};


/*const float problem_t::default_costs_[] = {
    1, 2, 3, 4, std::numeric_limits<float>::max()
};*/

inline std::ostream& operator<<(std::ostream &os, const problem_t &p) {
    p.print(os);
    return os;
}

class scaled_heuristic_t : public Heuristic::heuristic_t<state_t> {
    const Heuristic::heuristic_t<state_t> *h_;
    float multiplier_;
  public:
    scaled_heuristic_t(const Heuristic::heuristic_t<state_t> *h, float multiplier = 1.0)
      : h_(h), multiplier_(multiplier) { }
    virtual ~scaled_heuristic_t() { }
    virtual float value(const state_t &s) const {
        return h_->value(s) * multiplier_;
    }
    virtual void reset_stats() const { }
    virtual float setup_time() const { return 0; }
    virtual float eval_time() const { return 0; }
    virtual size_t size() const { return 0; }
    virtual void dump(std::ostream &os) const { }
    float operator()(const state_t &s) const { return value(s); }
};

class zero_heuristic_t: public Heuristic::heuristic_t<state_t> {
  public:
    zero_heuristic_t() { }
    virtual ~zero_heuristic_t() { }
    virtual float value(const state_t &s) const { return 0; }
    virtual void reset_stats() const { }
    virtual float setup_time() const { return 0; }
    virtual float eval_time() const { return 0; }
    virtual size_t size() const { return 0; }
    virtual void dump(std::ostream &os) const { }
    float operator()(const state_t &s) const { return value(s); }
};


