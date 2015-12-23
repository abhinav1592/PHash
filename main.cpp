//Working Version --> O(n) complexity for searching///////////

#include <bits/stdc++.h>
#define NHASH 113
#define MULTIPLIER 31
#define MAX 1196892
#define TABLE_SIZE 7459   // This is primary level table size
#define PRIME_MAX 300299

#define PRIME_LEVEL_PRIME 1196891
#define SECONDARY_LEVEL_PRIME 1299061
#define SUPER_PRIME  5381
#define GOD_PRIME 2897

#define STRING_BASE_ONE 13
#define STRING_BASE_TWO 61
#define MIN_VALUE 500
#define SKIP_VALUE 1
#define RUN_VALUE 1500


//#define PRIME_LEVEL_PRIME 2147483647

//#define SECONDARY_LEVEL_PRIME 524287

//#define SUPER_PRIME  789331
//#define STRING_BASE 13
#define ULL long long



/*

For base  = 13 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   and TABLE_SIZE = SECONDARY_LEVEL_PRIME and SUPER_PRIME = 789331 -->  collisions = 32
  For base  = 61 and SUPER_PRIME = SECONDARY_LEVEL_PRIME  and TABLE_SIZE = SECONDARY_LEVEL_PRIME and SUPER_PRIME = 49939 -->  collisions = 45

   For base  = 13 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 36
    For base  = 13 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 36
    For base  = 17 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 44
    For base  = 26 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 49
    For base  = 37 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 57
    For base  = 41 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 64
    For base  = 43 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 55
    For base  = 47 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 55
    For base  = 53 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 60
    For base  = 59 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 52
    For base  = 61 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 54
    For base  = 67 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 57
    For base  = 71 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 57
    For base  = 79 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 57
    For base  = 83 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 57
    For base  = 89 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 57
    For base  = 97 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 57
    For base  = 101 and SUPER_PRIME = SECONDARY_LEVEL_PRIME   -->  collisions = 57

    For base  = 41 and SUPER_PRIME 5381  -->  collisions = 50
    For base  = 26 and SUPER_PRIME 5381  -->  collisions = 120



    September 6
    At primary level:
    Minimum collision 6 at prime number 7459
    Minimum collision 5 at prime number 11503
    ============
    At secondary level
    2897 - collision = 0


*/

using namespace std;

// //////////////////---------STEP -1----------------------- ///////////////////////////
// We have to precalculate (base^i mod PRIME_LEVEL_PRIME) and (base^i mod SECONDARY_LEVEL_PRIME) and store them into arrays of size 100
int i,j,k,l;


ULL power_modulo(ULL base, ULL exp, ULL modulus)
{

    base %= modulus;
    ULL result = 1;
    while (exp > 0)
    {
        if (exp & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

ULL int power_array_level_one[100],power_array_level_two[100];
void precalculate()
{
    cout<<"\n Precaluation started.....\n";
    for(i=0; i<100; i++)
    {
        power_array_level_one[i]=power_modulo(STRING_BASE_ONE,i,PRIME_LEVEL_PRIME);
        power_array_level_two[i]=power_modulo(STRING_BASE_TWO,i,SECONDARY_LEVEL_PRIME);
    }
    cout<<"\n Precaluation complete.....\n";

}

// //////////////////---------STEP -1 OVER !----------------------- ///////////////////////////


//// //////////////////---------STEP - 2 ----------------------- ///////////////////////////

// For each string we are now going to hash_first_level it and store it into first level hash_first_level table
//     convert each character into string
//     mutiply each converted character with base^i
//     where i is the position of the character in the test string


ULL int h1,h2,counter1[MAX],counter2[MAX],hash_second_level[TABLE_SIZE][GOD_PRIME];
ULL hash_first_level[PRIME_MAX],sum1=0;
ULL int p,ctr1=0,ctr2=0;

//sort(special_prime,special_prime+185);
void build_hash_first_level_of_test_strings(string s[],int k)
{
//    for(p = MIN_VALUE;p<RUN_VALUE;p+=SKIP_VALUE)
//   {
    int number_of_test_strings = k;
    // cout<<"\n For "<<p<< " --> : ";

    for(i=0; i<number_of_test_strings; i++)
    {
        //cout<<" For i : "<<i<<" "<<endl;
        // Convert each string to its hash_first_level value

        h1 = 0;
        h2=0;
        //  int length_of_test_string = s[i].length();
        int length_of_test_string=100;
        for(j=length_of_test_string-1; j>=0; j--)
        {
            //  cout<<" For j : "<<j<<" h1 : "<<h1<<" s[i][j] : "<<s[i][j]<<" (s[i][j]-65) =  "<<(s[i][j]-65)<<endl;
            h1+=((((s[i][j]-65)*power_array_level_one[100-j-1])%PRIME_LEVEL_PRIME)%PRIME_LEVEL_PRIME) ;
            h2+=((((s[i][j]-65)*power_array_level_two[100-j-1])%SECONDARY_LEVEL_PRIME)%SECONDARY_LEVEL_PRIME) ;
        }


        // cout<<"\n hash_first_leveled values of string "<<i<<" --> "<<h1;

        counter1[i]=h1%PRIME_LEVEL_PRIME;
        hash_first_level[(h1%PRIME_LEVEL_PRIME)%TABLE_SIZE]++;

        counter2[i]=h2%SECONDARY_LEVEL_PRIME;


        //   cout<<"\n Primary hashed values of string "<<i<<" --> "<<counter1[i];
        //   cout<<"\n Secondary hashed values of string "<<i<<" --> "<<counter2[i];
        //  cout<<" \nPosition in table --> "<<counter1[i]%TABLE_SIZE;

    }
//
//    cout<<"\nzzzz Checking for duplicates in hash values ! \n";
//    sort(counter1,counter1+number_of_test_strings);
//    sort(counter2,counter2+number_of_test_strings);
//     for(i=0;i<number_of_test_strings-1;i++)
//     {
//         if(counter1[i]==counter1[i+1])  { cout<<" "<<counter1[i]<<" \n"; }
//     }
//     cout<<"\n Counter 1 complete \n" ;
//     for(i=0;i<number_of_test_strings-1;i++)
//     {
//         if(counter2[i]==counter2[i+1])  { cout<<" "<<counter2[i]<<" \n"; }
//     }
//     cout<<"\n Counter 2 complete \n" ;
//     cout<<"\nzzzz Checking complete !! \n";



//
//     for(i=0;i<number_of_test_strings;i++)
//     {
//          cout<<" Hash value of string(primary) " <<i<<" --> " <<counter1[i]<<endl;
//          cout<<" Hash value of string(sec.dary) " <<i<<" --> " << counter2[i]<<endl;
//     }
//        cout<<"\nzzzz\n";


    //cout<<"\n Maximum value in counter1 array -->"<< *max_element(counter1,counter1+number_of_test_strings);
    //cout<<"\n Maximum value in counter2 array -->"<< *max_element(counter2,counter2+number_of_test_strings);
    ULL sum=0,ctr3=0;


    // Checking the number of hash conflicts in primary table!


    for(i=0; i<TABLE_SIZE; i++)
    {
        if(hash_first_level[i]>0)
        {
            //cout<<"\n hash_first_level ["<<i<<"] : "<<hash_first_level[i]<<" ";
            sum+=hash_first_level[i];
        }
        else
        {
            ctr3++;
        }
    }


// //////////////////---------STEP - 2 OVER !----------------------- ///////////////////////////

//// //////////////////---------STEP - 3 Resolving collisions at secondary level ----------------------- ///////////////////////////

    // Checking special array for correct values
//   for(i=0;i<185;i++) cout<<special_array[i]<<",";
//   cout<<endl;
//   for(i=0;i<185;i++) cout<<special_prime[i]<<",";
//   cout<<endl;

    for(i=0; i<TABLE_SIZE; i++)
    {
        //cout<<" hash at "<<i<< " --> "<<hash_first_level[i]<< " \n";
        if(hash_first_level[i]>1)
        {
            /* Concept--> If hash_first_level[i] is greater than 1 then it means that there are
             are multiple hash values that collide in that area and we are going to resolve that
             using secondary table at each slot where we are again going to store the hashed string
             values of conflicting strings modulo some prime number. */

            // First we find those strings who have conflicting hash values
            // by iterating over counter1 array in which we have stored the values
            // of hashed values of each string
            //  bool flag=true;

            for(j=0; j<number_of_test_strings; j++)
            {
                if(counter1[j]%TABLE_SIZE==i )
                {
                    hash_second_level[i][(counter2[j]%SUPER_PRIME)%GOD_PRIME]++;
                }
            }

        }
    }


    //Checking for collisions at secondary level
//    cout<<"\n Secondary table : \n";
//  bool tf;
//    int arr[TABLE_SIZE],temp_ctr=0;
//    for(i=0;i<TABLE_SIZE;i++)
//        {
//           if(hash_first_level[i]>1)
//            {  cout<<" For i : "<<i<<" "<<endl;
//                tf=true;
//                for(j=0;j<GOD_PRIME;j++)
//                {
//                    cout<<" "<<hash_second_level[i][j]<<" ";
//
//                    if(hash_second_level[i][j]>1) {
//                            cout<<"LOOK HERE!!";
//
//                    //}
//
//                    //if(hash_second_level[i][j]>1)
//                    //{
//                       // cout<<"Slot i : "<<i<<" hash value --> "<<hash_second_level[i][j]<<" \n";
//                       if(tf==true ) {arr[temp_ctr++]=i; tf=false;}
//                    }
//
//
//                }
//                cout<<endl;
//            }
//        }

    // Now arr stores At exactly which slots the collisions are taking place
//        cout<<"\n Slot at which collision is taking place! \n";
//        for(i=0;i<temp_ctr;i++)
//        {
//            cout<<" "<<arr[i]<<",";
//        }
//        cout<<endl;
//        cout<<"-->"<<temp_ctr<<endl;


    sum1=*max_element(hash_first_level,hash_first_level+TABLE_SIZE);
    // cout<<" Maximum value in hash_first_leveled array -->"<<sum1<<endl;
    // cout<<"\n Number of empty slots in first table --> "<<ctr3<<endl;
    // cout<<"\n Number of filled slots in first table --> "<<TABLE_SIZE-ctr3+1<<endl;
    // cout<<"\n Final _ Sum of ni 's --> "<<sum<<endl;



}








ULL get_hash_value_of_first_part_of_main_string(string t,ULL i,ULL j,bool flag)
{
    //cout<<" start : "<<i<<" end : "<<j<<endl;

    // cout<< " bool flag --> "<<flag<<endl;

    long long d,h1=0, h2=0,c=99;//,absval;
    for(d=j-1; d>=i; d--)
    {
        //cout<<"\n d --> "<<d<<" ";
        if(flag==true)
        {
            //  cout<<"\n t["<<d<<"] "<<t[d]<<" (t["<<k<<"]-65) : "<<(t[d]-65)<< " power_array_level_one[100-"<<c<<"-1] "<<power_array_level_one[100-c-1]<<endl;
            // cout<<" Product of above two  -->  "<<((t[d]-65)*power_array_level_one[100-c-1]) <<" mod "<<PRIME_LEVEL_PRIME<< " --> "<< (((t[d]-65)*power_array_level_one[100-c-1])%PRIME_LEVEL_PRIME);
            h1+=((((t[d]-65)*power_array_level_one[100-c-1])%PRIME_LEVEL_PRIME)%PRIME_LEVEL_PRIME) ;
            h1%=PRIME_LEVEL_PRIME;
            flag=true;
            //  cout<<"\nflag true "<<k<<" h1 --> "<<h1 << " ";
        }

        else
        {
            // cout<<"\nflag false "<<k<<" h2 --> "<<h2 << " ";
            // cout<<"\n t["<<d<<"] "<<t[d]<<" (t["<<k<<"]-65) : "<<(t[d]-65)<< " power_array_level_one[100-"<<c<<"-1] "<<power_array_level_one[100-c-1]<<endl;
            // cout<<" Product of above two  -->  "<<((t[d]-65)*power_array_level_two[100-c-1]) <<" mod "<<SECONDARY_LEVEL_PRIME<< " --> "<< (((t[d]-65)*power_array_level_two[100-c-1])%SECONDARY_LEVEL_PRIME);

            h2+=((((t[d]-65)*power_array_level_two[100-c-1]%SECONDARY_LEVEL_PRIME))%SECONDARY_LEVEL_PRIME) ;
            h2%=SECONDARY_LEVEL_PRIME;
        }
        c--;
    }

    if(flag==true)
    {
        // cout<<"\n h1 "<<h1%PRIME_LEVEL_PRIME<<endl;
        return h1%PRIME_LEVEL_PRIME;
    }
    else
    {
        //cout<<"\n h2 "<<h2%SECONDARY_LEVEL_PRIME<<endl;
        return h2%SECONDARY_LEVEL_PRIME;
    }


}


int main()
{
    std::ios::sync_with_stdio(false);
    freopen ("in.txt","r",stdin);
    freopen ("out.txt","w",stdout);
    cout<<" I got here!";
    precalculate();



    int i,t,k;
    string s;
    // cin>>t;
    // while(t--)
    {
        //cout<<" t : "<<t<<endl;
        cin>>s;
        int length_of_main_string = s.length();
        // cin>>k;
        k=10000;
        // cout<<" s length : "<<length_of_main_string<<" k : "<<k<<endl;
        string test_strings[k+1];
        for(i=0; i<k; i++)
        {
            cin>>test_strings[i];
        }

        build_hash_first_level_of_test_strings(test_strings,k);

        //sort(counter1,counter1+TABLE_SIZE);
//        for(int h=0;h<k;h++)
//        {
//            cout<<" For string " <<h<<" -- \n" <<test_strings[h]<<"\n counter-1 hash --> "<<counter1[h]<< " counter-2 hash --> "<<counter2[h]<<endl;
//        }

        // hash_first_leveling the Main string and checking into hash_first_leveled array!
        int string_match_counter_primary=0,string_match_counter_secondary=0;
        ULL hash_value_of_first_part_of_main_string,temp1,temp2;

        cout<<" Main String length : "<<length_of_main_string<<" ";
        bool flag=false;

        for(i=0; i<length_of_main_string-100; i++)
        {
            //  cout<<"\n\n For i --- < s[i]--> "<<s[i]<<endl;
            // if(i==99397)
            {
                hash_value_of_first_part_of_main_string = get_hash_value_of_first_part_of_main_string(s,i,i+100,true);
                temp1=hash_value_of_first_part_of_main_string;

                temp2=get_hash_value_of_first_part_of_main_string(s,i,i+100,false);
                //cout<<" Temp1--> "<<temp1<< " Temp2--> "<<temp2;
            }


            //   cout<<" Temp1--> "<<temp1<< " Temp2--> "<<temp2;
            //   cout<<" Position of "<<temp1<<" in table --> "<<temp1%TABLE_SIZE;
            //   cout<<" \n hash_first_level["<<temp1%TABLE_SIZE<<"] --> " <<hash_first_level[temp1%TABLE_SIZE];
            if(hash_first_level[temp1%TABLE_SIZE]==1)
            {
                // cout<<"\n String hashed at primary level! \n";

                int h;
                for(h=0; h<k; h++)
                {
                    if(counter1[h]==temp1)
                    {
                        // cout<<" counter["<<h<<"] --> "<<counter1[h]<<endl;

                        if(test_strings[h].compare(0,100,s,i,100)==0)
                        {
                            cout<<"\n String matched at primary level! \n";
                            flag=true;
                            string_match_counter_primary++;
                            cout<<test_strings[h]<<endl;
                        }
                    }
                }
                //   cout<<endl;
            }
            else if(hash_first_level[temp1%TABLE_SIZE]>1)
            {
                // It means we have a match but we are not sure because other strings also hashed to the same slot
                // so we calculate secondary hash of current string under consideration
                //   temp2=get_hash_value_of_first_part_of_main_string(s,i,i+100,first);
                // cout<<"\n String hashed at secondary level! \n";
                if(hash_second_level[temp1%TABLE_SIZE][(temp2%SUPER_PRIME)%GOD_PRIME]==1)
                {
                    int h;
                    for(h=0; h<k; h++)
                    {
                        if(counter2[h]==temp2)
                        {
                            // cout<<" counter["<<h<<"] --> "<<counter2[h]<<endl;
                            if(test_strings[h].compare(0,100,s,i,100)==0)
                            {
                                cout<<"\n String matched at secondary level! \n";
                                flag=true;
                                string_match_counter_secondary++;
                                cout<<test_strings[h]<<endl;
                            }
                        }
                    }
                }
                // cout<<endl;
            }

            // Move the pointer forward by calculating the hash value of i+1 to j+1 position in the main string

            //  cout<<"\n s ["<<i+1<<"] "<<s[i+1]<<" (s["<<i+1<<"]-65) : "<<(s[i+1]-65)<< " STRING_BASE_ONE "<<STRING_BASE_ONE<<" temp1 "<<temp1<<endl;cout <<" temp1 -->  "<<((s[i+1]-65)+((STRING_BASE_ONE%PRIME_LEVEL_PRIME)*(temp1%PRIME_LEVEL_PRIME)%PRIME_LEVEL_PRIME)%PRIME_LEVEL_PRIME)<<endl;
            temp1=((s[i+1]-65)+((STRING_BASE_ONE%PRIME_LEVEL_PRIME)*(temp1%PRIME_LEVEL_PRIME)%PRIME_LEVEL_PRIME)%PRIME_LEVEL_PRIME);

            // Move the pointer forward by calculating the hash value of i+1 to j+1 position in the main string
            //  cout<<"\n s ["<<i+1<<"] "<<s[i+1]<<" (s["<<i+1<<"]-65) : "<<(s[i+1]-65)<< " STRING_BASE_TWO "<<STRING_BASE_TWO<<" temp2 "<<temp2<<endl;cout<<" STRING_BASE_TWO*temp2 -->  "<<STRING_BASE_TWO*temp2;cout <<" temp2 -->  "<<((s[i+1]-65)+((STRING_BASE_TWO%SECONDARY_LEVEL_PRIME)*(temp2%SECONDARY_LEVEL_PRIME)%SECONDARY_LEVEL_PRIME)%SECONDARY_LEVEL_PRIME)<<endl;
            temp2=((s[i+1]-65)+((STRING_BASE_TWO%SECONDARY_LEVEL_PRIME)*(temp2%SECONDARY_LEVEL_PRIME)%SECONDARY_LEVEL_PRIME)%SECONDARY_LEVEL_PRIME);
        }



        if(flag==false) cout<<"\n No string matches!!\n";
        else
        {
            cout<<" At primary level --> "<<string_match_counter_primary<< "\n At secondary level --> "<<string_match_counter_secondary<<endl;
            cout<<"\n Total Number of strings matched : --> "<<string_match_counter_primary+string_match_counter_secondary<<endl;
        }

    }
    //   fclose(stdout);
    return 0;
}
