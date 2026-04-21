#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double calculate_binomial_probability(int n, int k, double p)
{
    if (k < 0 || k > n)
        return 0.0;
    if (k == 0)
        return pow(1.0 - p, n);
    if (k == n)
        return pow(p, n);

    double prob = pow(1.0 - p, n);

    for (int i = 1; i <= k; i++)
    {
        prob = prob * (n - i + 1) / i;
        prob = prob * (p / (1.0 - p));
    }

    return prob;
}

int main()
{
    // Task 1
    // Part A
    float hit_chance = 0.75f;
    float prob_1_a = calculate_binomial_probability(4, 3, hit_chance);

    printf("The chance, that player hits target 3 times in 4 attemps is: %.3f\n", prob_1_a);

    // Part B
    float attack_attempts = 100.0f;
    float expected_hit_count = hit_chance * attack_attempts;

    printf("The expected number of successful hits is: %.3f\n", expected_hit_count);

    // Part C
    float attacks = 100.0f;
    float misses = 30.0f;
    float total_prob = 0.0f;
    for (int i = misses; i <= attacks; i++)
    {
        total_prob += calculate_binomial_probability(attacks, i, 1 - hit_chance);
    }

    printf("Chance, that player will miss at least 30 times in 100 attacks is: %.3f\n", total_prob);

    // Task 2
    // Part A
    float enemies = 50.0f;
    float prob_of_rare = 0.05f;
    float prob_no_rare = pow(1 - prob_of_rare, enemies);

    printf("Chance, that player will get no rare items from 50 enemies is: %.3f\n", prob_no_rare);

    float prob_atleast_one = 1 - prob_no_rare;

    printf("Chance, that player will get at least one rare item from 50 enemies is: %.3f\n", prob_atleast_one);

    return 0;
}