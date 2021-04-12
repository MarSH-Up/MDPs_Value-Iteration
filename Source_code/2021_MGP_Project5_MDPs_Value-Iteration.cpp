/* Assigment 5: MDPs Value Iteration
 * Description: Implement the the value iteration algorithm to solve a discrete MDP.
 *
 * Version: 1.0
 * Date: 2021 April
 * By: Mario De Los Santos
 * Instituto Nacional de Astrofísica Óptica y Electónica.
 *
 * Class: Probabilistic Graphical Models
 * By: PhD Enrique Sucar
 *
 * Reference; Sucar, L. E. (2015). Probabilistic graphical models.
 *            Advances in Computer Vision and Pattern Recognition.
 *            London: Springer London. doi, 10(978), Chapter 11
 */
#include <iostream>
using namespace std;
/*How to use the class:
 *
 * Read the description of the parameters to a better comprehension.
 *
 * The Class MDP_Value_Iteration includes two main algorithms and one constructor, those are called as we will show subsequently:
 *
 * Example:
 *  Object creation:
 *   - MDP_Value_Iteration MDP_Example (No_states: 12, No_actions: 4, Rewards matrix: floats, Transition Matrix: floats, discountFactor(y):0.9);
 *
 *   1. Value Iteration:
 *      int* PolicyValue = MDP_Example.Value_Iteration(States starting reward: array[No_states],
 *                                                      Threshold: parameter to define convergence,
 *                                                      Discount Factor(y): float);
 *
 *   2. int* PolicyPolicy = MDP_Example.Policy_Iteration(States starting reward: array[No_states],
 *                                                      Threshold: parameter to define convergence,
 *                                                      Discount Factor(y): float);
 *                                                      
 * The fuctions would return you an array[No_states] with the best policy path.
 * */
class MDP_Value_Iteration
{
    /* Predefinition for out Matrixes, you can avoid this using vector,
     *                  but I think that adds some complexity don't need */
    #define No_state_limit 100
    #define NO_actions_limit 50

    //Some Pre details to get the information in the class
    int No_states_class; //Set of states = S1, ..., Sn
    int No_actions_class; //Set of actions = U, D, R, L in gridworld

/*R(s, a) is the reward that the agent receives if it takes an action A in state S.
 * Consider that we are adding the information from the object creation, so you need to specify the
 * matrix with the pre-defined structure (This applies to Rewards_Class and Transitions_Class
 * */ double Rewards_Class[No_state_limit][NO_actions_limit]={0};

 /*Transition Matrix, is the fuction that maps the states, S, and the actions,A, to new states S'
 * it is specified as a probability distribution.
 * */ double Transition_Class[No_state_limit][NO_actions_limit]={0};


public:
    MDP_Value_Iteration(int No_states, int No_actions,float *Rewards, float *Transition, float discountFactor){
        //This just follows a Data Hiding Philosophy, saving the needs in the class
        No_actions_class = No_actions;
        No_states_class = No_states;
        /*Matrixes Structures:
         *- Rewards Matrix: is a matrix NxM, where N is the number of states and M the number of Actions
         * The matrix describes the reward that each state earn reaching the next state by an action,
         * example: The state 0 in the bot example can reach state 4 and state 1, so the description will be:
         *                  //Up Down Right Left
         *      R(So, a) =   {1,    0,    1,  0}
         *
         *  So the Final Matrix need to have the same structure for Rn(Sn, a),
         *                                      where Sn are all the states in the grid.
         *
         * - Transition Matrix: is the matrix that defines the probability of each state to move to any other, in other words
         *   The matrix describes the probability of each state to take any action.
         *
         *   Example: Lets take again the state 0, so we can reach state 4 and 1, considering that lets describe the Transition
         *                              //Up Down Right Left
         *      Transition S0(AxSxS') = {0.8,  0,   0.1, 0.1}
         *
         * Note that we include a probability of 0.1 to move to Left, but any state can be reached in that direction, that
         * means that the state can keep in the same position. These for each state!
         * */
        for(int i=0;i<No_states;i++) {
            for (int j = 0; j < No_actions; j++) {
               Rewards_Class[i][j]=*(Rewards + i * No_actions + j);
               Transition_Class[i][j]=*(Transition+ i * No_actions + j);
            }
        }
    }
    int* Value_Iteration(float Start[],float Threshold,float Discount)
    {
        /*This algorithm is based on Bellman's Equation you can review it in Chapter 11 of the book, page 201.
         *
         * Brief Description, the algorithm calculate the values that each state will reach considering the rewards and
         * transitions, we divide the equation in two, so the Bellman's Equation:
         *
         *                  Vt(S) = max {R(s,a) + yE(Transition(a,s, s')Vt-1(s'), Please see the equation in the Readme file
         *
         * So we divided into:
         *                      v = yE(Transition(a,s, s')Vt-1(s')......(1)
         *                      m = max {R(s,a)}........................(2)
         *
         * Please see the chapter as a deeper reference.
         *
         * For the Value Iteration class you need to pass a Start state's rewards, as a start point to calculate the following iterations
         * I would recommend you to use 1 for the states, 100 for the goal, and -100 for those "endpoints"
         * */
        cout<<"Value Iteration"<<endl;

        //The following variables would storage the rewards of the states and the iterative values that those would get
        double Vt[No_states_class];
        double Vo[No_states_class];

        //The policy would describe the best path to follow
        int* Policy; //We use a pointer in heap memory to return in using OOPs principles
        Policy = new int[No_states_class];

        for(int i=0;i<No_states_class;i++)
            Vo[i] = Start[i]; //We storage the default states in the Vo variable.

        double v = 0.0; //First equation variable
        double m; //Second equation variable
        int convergence=0; //Convergence variable
        int iterations=0; //Iteration counter

        do {//We decided to use a do while, so we calculate before to stop the process
            for(int i=0;i<No_states_class;i++) {

                v = 0.0;
                m = -100;//We set it in -100 just to make sure the operations can pass the value.

                for(int j = 0; j < No_actions_class; j++)
                    v += (Discount*(Transition_Class[i][j] * Vo[i])); // Equation 1
                double n;
                for(int y=0;y<No_actions_class;y++)
                {
                    n=0.0;
                    n = Rewards_Class[i][y] + v; //Equation 2 with the addition of the equation 1.
                    if(n>m) //Search the max value
                    {
                        m=n;
                        Policy[i]=y; //SaVe the best action to use, remember that the for loop is traveling around the number of actions.
                    }
                }
                Vt[i] = m; //Then we storage the value in the Vt variable
            }
            /*
            cout<<"Vo: {";
            for(int i = 0; i < No_states_class; i++)
                cout<<Vo[i]<<",";
            cout<<"}"<<endl;
            cout<<"Vt: {";
            for(int i = 0; i < No_states_class; i++)
                cout<<Vt[i]<<",";
            cout<<"}"<<endl;*/
            iterations++; //Iterations counter
            for(int i=0;i<No_states_class;i++)
            {
                double l = abs(Vt[i]-Vo[i]); //if the difference between the value T and the t-1 is less than the Threshold (Defined by you)
                //then we count this and if we count it in all the states, then next step
                if(l<Threshold)
                    convergence++;
            }
            if(convergence==12){
                cout<<"Done at "<<iterations<<endl; //Print the number of iteractions
                //cout<<"Steps: ";
                //for(int i=0; i<No_states_class;i++)
                    //cout<<Policy[i]<<",";

                //cout<<endl;
                cout<<"Remember: Up -> 0, Dowm -> 1, Right -> 2, Left -> 3"<<endl;
                break; //break the whille
            }
            else { //If we dont convergence yet, we save the t value to be the new t-1
                for (int i = 0; i < No_states_class; i++)
                    Vo[i] = Vt[i];
                convergence=0;//reset the count
            }

        }while(1);

        return Policy;
        delete[] Policy; //Delete the space in the heap memory
    }
    int* Policy_Iteration(float Start[],float Discount)
    {
        /*This algorithm is based on Bellman's Equation you can review it in Chapter 11 of the book, page 201.
        *
        * Brief Description, the algorithm calculate the values that each state will reach considering the rewards and
        * transitions, we divide the equation in two, so the Bellman's Equation:
        *
        *                  Vt(S) = max {R(s,a) + yE(Transition(a,s, s')Vt-1(s'), Please see the equation in the Readme file
        *
        * So we divided into:
        *                      v = yE(Transition(a,s, s')Vt-1(s')......(1)
        *                      m = max {R(s,a)}........................(2)
        *
        * Please see the chapter as a deeper reference.
        *
        * For the Value Iteration class you need to pass a Start state's rewards, as a start point to calculate the following iterations
        * I would recommend you to use 1 for the states, 100 for the goal, and -100 for those "endpoints"
        *
        * Note that the main difference between this algorithm and the Value iteration is that we are using a Dynamic principle, using
        * the memory to store the policy value, so instead of comparing the t and t-1 value of the states to be smaller than the defined
        * Threshold, we compare the changes in the policy paths.*/
        cout<<"Policy Iteration"<<endl;
        double Vt[No_states_class];
        double Vo[No_states_class];
        int OldPolicy[No_states_class];//Array to save the t-1 policy
        int* Policy;
        Policy = new int[No_states_class];

        for(int i=0;i<No_states_class;i++)
            Vo[i] = Start[i];
        double v = 0.0;
        double m;
        int convergence=0;
        int iterations=0;
        do {
            for(int i=0;i<No_states_class;i++) {
                v = 0.0;
                m = -100;
                for(int j = 0; j < No_actions_class; j++)
                    v += (Discount*(Transition_Class[i][j] * Vo[i])); //Equation 1
                double n;
                for(int y=0;y<No_actions_class;y++)
                {
                    n=0.0;
                    n = Rewards_Class[i][y] + v; //Addition of the Equation 1 + 2
                    if(n>m) //Max value calculation
                    {
                        m=n;
                        Policy[i]=y; //Save the best action to use, remember that the for loop is traveling around the number of actions.
                    }
                }
                Vt[i] = m;
            }
            /*
            cout<<"Vo: {";
            for(int i = 0; i < No_states_class; i++)
                cout<<Vo[i]<<",";
            cout<<"}"<<endl;
            cout<<"Vt: {";
            for(int i = 0; i < No_states_class; i++)
                cout<<Vt[i]<<",";
            cout<<"}"<<endl;*/
            iterations++;
            for(int i=0;i<No_states_class;i++)
            {

                /*Look carefully the Algorith in the Readme file, you can see that the conditional now is to compare the last iteration policy
                 * with the new one, so if there are the same, we break the loop winning speed at storage cost, see the description in the
                 * chapter 11 of the book to understand the algorithm complexity
                 * */
                if(Policy[i]==OldPolicy[i])
                    convergence++; //If each one of the steps are the same
            }
            if(convergence==12){
                cout<<"Done at "<<iterations<<endl;
                //cout<<"Steps: ";
                //for(int i=0; i<No_states_class;i++)
                //cout<<Policy[i]<<",";

                //cout<<endl;
                cout<<"Remember: Up -> 0, Dowm -> 1, Right -> 2, Left -> 3"<<endl;
                break;
            }//break the loop
            else { //If not, then save the new Policy in the old one, to compare in the next iteration
                for (int i = 0; i < No_states_class; i++) {
                    Vo[i] = Vt[i];
                    OldPolicy[i] = Policy[i];
                }
                convergence=0;
            }
        }while(1);
        return Policy; //Return the policy
        delete[] Policy; //delete the heap memory pointer.
    }
};
int main() {
    int No_states = 12; //S = {s0, s1, ... , s10}
    int No_actions = 4; //UP, DOWM, RIGHT, LEFT
    float Discount_Factor = 0.9;

    //Bear Example
                                 //0  1  2  3  4  5  6   7 8 9  10  11
    float Start_values[No_states]={1, 1, 1, 1, 1, 1,-100,1,1,1,-100,100};

                                         //UP, DOWM, RIGHT, LEFT
    float Rewards[No_states][No_actions] = { {0,-1,1,0}, //State 0
                                             {0,-1,1,1}, //State 1
                                             {0,-100,1,1}, //s 2
                                             {0,1,1,0}, //S 3
                                             {1,1,1,0}, //S 4
                                             {1,1,-100,1}, //S 5
                                             {1,-100,1,1}, //S 6
                                             {1,100,0,-100}, //S 7
                                             {1,0,1,0}, //S 8
                                             {1,0,-100,1}, //S 9
                                             {-100,0,100,1},//S 10
                                             {1,100,0,-100}}; //S11

                                             //UP, DOWM, RIGHT, LEFT
    float Transitions[No_states][No_actions] = { {0,0.8,0.2,0}, //State 0
                                                 {0,0.1,0.8,0.1}, //State 1
                                                 {0,0.1,0.8,0.1}, //s 2
                                                 {0,0.8,0.1,0}, //S 3
                                                 {0.1,0.1,0.8,0}, //S 4
                                                 {0.7,0.1,0.1,0.1}, //S 5
                                                 {0.1,0.1,0.7,0.1}, //S 6
                                                 {0.1,0.8,0,0.1}, //S 7
                                                 {0.8,0,0.2,0}, //S 8
                                                 {0.8,0,0.1,0.1}, //S 9
                                                 {0.1,0,0.8,0.1},//S 10
                                                 {0.1,0.8,0,0.1}};//s11

    /* Bot Example
     * float Start_values[No_states]={1,1,1,1,1,0,1,-100,1,1,1,100};
     * float Rewards[No_states][No_actions] = { {1,0,1,0}, //State 0
                                           {0,0,1,1}, //State 1
                                           {1,0,1,1}, //s 2
                                           {-100,0,1,0}, //S 3
                                           {1,1,0,1}, //S 4
                                           {0,0,0,0}, //S 5 Dead state
                                           {1,1,-100,1}, //S 6
                                           {100,1,0,1}, //S 7
                                           {0,-1,1,0}, //S 8
                                           {0,0,1,1}, //S 9
                                           {0,1,100,1},//S 10
                                           {0,-100,0,1}}; //S11
    * float Transitions[No_states][No_actions] = { {0.8,0,0.1,0.1}, //State 0
                                               {0,0.1,0.8,0.1}, //State 1
                                               {0.1,0.1,0.7,0.1}, //s 2
                                               {0.1,0,0.8,0.1}, //S 3
                                               {0.8,0.1,0,0.1}, //S 4
                                               {0,0,0,0}, //S 5
                                               {0.8,0.1,0,0.1}, //S 6
                                               {0.8,0.1,0.1,0}, //S 7
                                               {0.1,0.1,0.8,0}, //S 8
                                               {0.1,0,0.8,0.1}, //S 9
                                               {0,0.1,0.8,0.1},//S 10
                                               {0.8,0.1,0.1,0}};//s11
    } */
    //Object creation
    MDP_Value_Iteration MDP_1(No_states, No_actions, (float*)Rewards, (float*)Transitions, Discount_Factor);
    
    //Function call Value iteration
    int* Policy_ValueIteration = MDP_1.Value_Iteration(Start_values, 0.1, Discount_Factor);
    for(int i=0;i<No_states;i++)
        cout<<Policy_ValueIteration[i]<<",";
    cout<<endl;
    
    //Function call Policy Iteration
    int* Policy_PolicyIteration = MDP_1.Policy_Iteration(Start_values,Discount_Factor);
    for(int i=0;i<No_states;i++)
        cout<<Policy_PolicyIteration[i]<<",";

    return 0;
}
