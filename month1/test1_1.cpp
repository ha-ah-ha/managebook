#include <bits/stdc++.h>
using namespace std;


int type[9];


struct card {
    int a, b;
    card(int a0, int b0) {
        a = a0;
        b = b0;
    }
    
};

bool type2(card c1, card c2, card c3, card c4, card c5) {
    vector<int> hand;
    hand.push_back(c1.a);
    hand.push_back(c2.a);
    hand.push_back(c3.a);
    hand.push_back(c4.a);
    hand.push_back(c5.a);
    sort(hand.begin(), hand.end());
    if ((hand[0] == hand[1] && hand[1] == hand[2] && hand[2] == hand[3]) || (hand[1] == hand[2] && hand[2] == hand[3] && hand[3] == hand[4]))
        return true;
    else
        return false;
}


bool type3(card c1, card c2, card c3, card c4, card c5) {
    vector<int> hand;
    hand.push_back(c1.a);
    hand.push_back(c2.a);
    hand.push_back(c3.a);
    hand.push_back(c4.a);
    hand.push_back(c5.a);
    sort(hand.begin(), hand.end());
    if ((hand[0] == hand[1] && hand[1] == hand[2] && hand[4] == hand[3]) || (hand[0] == hand[1] && hand[2] == hand[3] && hand[3] == hand[4]))
        return true;
    else
        return false;
}


bool type4(card c1, card c2, card c3, card c4, card c5) {
    if ((c1.b == c2.b) && (c2.b == c3.b) && (c3.b == c4.b) && (c4.b == c5.b))
        return true;
    else
        return false;
}


bool type5(card c1, card c2, card c3, card c4, card c5) {
    vector<int> hand;
    hand.push_back(c1.a);
    hand.push_back(c2.a);
    hand.push_back(c3.a);
    hand.push_back(c4.a);
    hand.push_back(c5.a);
    sort(hand.begin(), hand.end());
    if ((hand[1] - hand[0] == 1) && (hand[2] - hand[1] == 1) && (hand[3] - hand[2] == 1) && (hand[4] - hand[3] == 1))
        return true;
    else
        return false;
}

bool type1(card c1, card c2, card c3, card c4, card c5) {
    if (type5(c1, c2, c3, c4, c5) && type4(c1, c2, c3, c4, c5)) {
        return true;
    }
    else
        return false;
}



bool type6(card c1, card c2, card c3, card c4, card c5) {
    vector<int> hand;
    hand.push_back(c1.a);
    hand.push_back(c2.a);
    hand.push_back(c3.a);
    hand.push_back(c4.a);
    hand.push_back(c5.a);
    sort(hand.begin(), hand.end());
    if ((hand[0] == hand[1] && hand[1] == hand[2] ) || (hand[1] == hand[2] && hand[2] == hand[3] ) || (hand[2]==hand[3] && hand[3] == hand[4]))
        return true;
    else
        return false;
}


bool type7(card c1, card c2, card c3, card c4, card c5) {
    vector<int> hand;
    hand.push_back(c1.a);
    hand.push_back(c2.a);
    hand.push_back(c3.a);
    hand.push_back(c4.a);
    hand.push_back(c5.a);
    sort(hand.begin(), hand.end());
    if ((hand[0] == hand[1] && hand[2] == hand[3]) || (hand[0] == hand[1] && hand[3] == hand[4]) || (hand[3] == hand[4] && hand[1] == hand[2]))
        return true;
    else
        return false;
}


bool type8(card c1, card c2, card c3, card c4, card c5) {
    vector<int> hand;
    hand.push_back(c1.a);
    hand.push_back(c2.a);
    hand.push_back(c3.a);
    hand.push_back(c4.a);
    hand.push_back(c5.a);
    sort(hand.begin(), hand.end());
    if ((hand[0] == hand[1] ) || (hand[1] == hand[2]) || (hand[2] == hand[3]) ||(hand[3] == hand[4]))
        return true;
    else
        return false;
}



int main() {
    int A, B;
    cin >> A >> B;
    int a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;
    card card1(a1, b1), card2(a2, b2);
    vector<card> selecard;
    for (int i = 0; i < A; ++i)
    {
        for (int j = 0; j < B; ++j)
        {
            if (!((i == a1 && j == b1) || (i == a2 && j == b2)))
            {
                selecard.push_back(card(i, j));
            }
        }
    }
    for (int i = 0; i < A * B - 4; i++) {
        for (int j = i + 1; j < A * B - 3; j++) {
            for (int k = j + 1; k < A * B - 2; k++) {
                if (type1(card1, card2, selecard[i], selecard[j], selecard[k]))
                    type[0]++;
                else if (type2(card1, card2, selecard[i], selecard[j], selecard[k]))
                    type[1]++;
                else if (type3(card1, card2, selecard[i], selecard[j], selecard[k]))
                    type[2]++;
                else if (type4(card1, card2, selecard[i], selecard[j], selecard[k]))
                    type[3]++;
                else if (type5(card1, card2, selecard[i], selecard[j], selecard[k]))
                    type[4]++;
                else if (type6(card1, card2, selecard[i], selecard[j], selecard[k]))
                    type[5]++;
                else if (type7(card1, card2, selecard[i], selecard[j], selecard[k]))
                    type[6]++;
                else if (type8(card1, card2, selecard[i], selecard[j], selecard[k]))
                    type[7]++;
                else
                    type[8]++;
            }
        }
    }
    for (int i = 0; i < 9; ++i)
    {
        cout << type[i] << " ";
    }

    return 0;
}

