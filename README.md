<h1>&#9968 Markov Decision Process' Value Iteration Algorithm</h1>

The content of this repository served as an assignment project requested for the course Probabilistic Graphical Models at the <a href="https://www.inaoep.mx/">INAOE</a> as a student of the Master in Science in Computer Science. All the resources presented in the versions of this code were obtained from the class book that you can find in the references part. 

<strong>This application of the algorithm and information was for an only educational purpose</strong>

<h3>Description:</h3> Implement the value iteration algorithm to solve a discrete Markov Decision Processes.

Professor:
- PhD <a href="https://ccc.inaoep.mx/~esucar/">Enrique Sucar</a>.

Student Involved:
- Mario De Los Santos. Github: <a href="https://github.com/MarSH-Up">MarSH-Up</a>. Email: madlsh3517@gmail.com


<em>Instructions</em>
1. Download the repository's file
2. Verify that the C++ version is at least C++ 14
3. Call the functions marked in the documentation

The following algorithms are based on the documentation provided by the professor. The book used as a reference is at the end of this file. 

1. The value iteration algorithm consists of iteratively estimate the value for each state, s, based on Bellman's equation. The next image shows the pseudocode used to create this project.

<div style="text-align:center"><img src="Images/Algorithm_pseudocode.PNG" /></div>

2. The Policy iteration algorithm consists of iteratively estimate the value for each state, s, based on Bellman's equation, with the main difference we store the Policy in each iteration, it would allow us to compare an iteration (t) with a (t-1), then if the Policy is the same we finish the process, this gives you a computational speed advantage at storage cost. The image 2 shows the pseudocode used to create this project.

<div style="text-align:center"><img src="Images/Algorithm_pseudocode1.PNG" /></div>

<em>Examples</em>
We used two examples to confirm the algorithm's functionality,  called "The robot path", from the book, and "The bear travel" from an online blog called Towards Data Science (Link in the references)

- ![The robot path](Images/Example_bot.PNG)
- ![The bear travel](Images/Example_bear.PNG)

- Let's start with the robot path example, consider figure 1 as a grid to complete, our code needs some parameters defined in the description, so the next image shows what we mean.
    - First, consider that the enumeration of the states follows:
    - - ![States](Images/Example_bot_states.PNG)
    - We pass the parameters as a matrixes, as you can see in the next figure: 
    - - ![Parameters Descriptions](Images/Example_bot_code.PNG)
    - Then running the fuctions you would see the following results:
    - ![Policy_Iteration](Images/Example_bot_iteraction.PNG)
    - ![Policy](Images/Example_bot_Policy.PNG)
    - So then, you would follow the next path
    - ![Policy](Images/Example_bot_solved.png)

- Let's solve now the second example, now we are just going to show the images of each fuction used and results:

    - ![States](Images/Example_bear.PNG)
    - ![Parameters Descriptions](Images/Example_bear_code.PNG)
    - ![Policy_Iteration](Images/Example_bear_policy.PNG)
#References
-  Sucar, L. E. (2020). Probabilistic graphical models. Advances in Computer Vision and Pattern Recognition.London: Springer London. doi, 10(978), Chapter 11.
- Mohammad Ashraf. (2018). Reinforcement Learning Demystified: Solving MDPs with Dynamic Programming. April 2021, de Towards Data Science Sitio web: https://towardsdatascience.com/reinforcement-learning-demystified-solving-mdps-with-dynamic-programming-b52c8093c919
