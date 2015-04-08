#include <bits/stdc++.h>
#define W 1
#define D 0
#define L -1
#define INF 1000

using namespace std;

struct Node {
  char state[3][3];
  int open;
};

int pl;
vector<Node> nei;

bool terminal_test(Node cur) { //--------------------TERMINAL TEST
  if((cur.state[0][0] == 'X' && cur.state[0][1] == 'X' && cur.state[0][2] == 'X')
     || (cur.state[1][0] == 'X' && cur.state[1][1] == 'X' && cur.state[1][2] == 'X')
     || (cur.state[2][0] == 'X' && cur.state[2][1] == 'X' && cur.state[2][2] == 'X')
     || (cur.state[0][0] == 'X' && cur.state[1][1] == 'X' && cur.state[2][2] == 'X')
     || (cur.state[2][0] == 'X' && cur.state[1][1] == 'X' && cur.state[0][2] == 'X'))
    return true;
  
  else if((cur.state[0][0] == 'O' && cur.state[0][1] == 'O' && cur.state[0][2] == 'O')
	  || (cur.state[1][0] == 'O' && cur.state[1][1] == 'O' && cur.state[1][2] == 'O')
	  || (cur.state[2][0] == 'O' && cur.state[2][1] == 'O' && cur.state[2][2] == 'O')
	  || (cur.state[0][0] == 'O' && cur.state[1][1] == 'O' && cur.state[2][2] == 'O')
	  || (cur.state[2][0] == 'O' && cur.state[1][1] == 'O' && cur.state[0][2] == 'O'))
    return true;
  
  else if(cur.open == 0)
    return true;
  
  return false;
}

int row(Node cur, int C) { //---------------IS ROW UP FOR COUNT?
  int x = 0, o = 0;
  for(int i = 0; i < 2; i++) {
    if(cur.state[i][C] == 'X')
      x++;
    else
      o++;
  }
  
  if(x > 0 && o > 0)
    return 10;
  else if(x > 0)
    return W;
  else if(o > 0)
    return L;
  return D;
}

int col(Node cur, int R) { //------------IS COLUMN UP FOR COUNT?
  int x = 0, o = 0;
  for(int i = 0; i < 2; i++) {
    if(cur.state[R][i] == 'X')
      x++;
    else
      o++;
  }
  
  if(x > 0 && o > 0)
    return 10;
  else if(x > 0)
    return W;
  else if(o > 0)
    return L;
  return D;
}

int diag1(Node cur) { //-----------IS DIAGONAL1 UP FOR COUNT?
  int ans = 0;
  int x = 0, o = 0;
  
  if(cur.state[0][0] == 'X' || cur.state[1][1] == 'X' || cur.state[2][2] == 'X')
    x++;
  if(cur.state[0][0] == 'O' || cur.state[1][1] == 'O' || cur.state[2][2] == 'O')
    o++;
    
  if(x > 0 && o > 0)
    ans = 10;
  else if(x > 0)
    ans = W;
  else if(o > 0)
    ans = L;
  else
    ans = D;

  return ans;
}

int diag2(Node cur) { //-----------IS DIAGONAL2 UP FOR COUNT?
  int ans = 0;
  int x = 0, o = 0;
  
  if(cur.state[0][0] == 'X' || cur.state[1][1] == 'X' || cur.state[2][2] == 'X')
    x++;
  if(cur.state[0][0] == 'O' || cur.state[1][1] == 'O' || cur.state[2][2] == 'O')
    o++;
  
  if(x > 0 && o > 0)
    ans = 10;
  else if(x > 0)
    ans = W;
  else if(o > 0)
    ans = L;
  else
    ans = D;

  return ans;
}

int diff(Node cur) { //--------------------------DIFF = MAX - MIN
  int min = 0, max = 0;
  
  for(int i = 0; i < 2; i++) {
    int r = row(cur, i), c = col(cur, i), d1 = diag1(cur), d2 = diag2(cur);
    //----------------------ROWS
    if(r == W)
      max++;
    else if(r == L)
      min++;
    else {
      min++;
      max++;
    }
    
    //-------------------COLUMNS
    if(c == W)
      max++;
    else if(c == L)
      min++;
    else {
      min++;
      max++;
    }
    
    if(d1 == W)
      max++;
    else if(d1 == L)
      min++;
    else {
      min++;
      max++;
    }

    if(d2 == W)
      max++;
    else if(d2 == L)
      min++;
    else {
      min++;
      max++;
    }
  }
  
  return max - min;
}

int utility(Node cur) { //-------------------------FUNCTION UTILITY
  if((cur.state[0][0] == 'X' && cur.state[0][1] == 'X' && cur.state[0][2] == 'X')
     || (cur.state[1][0] == 'X' && cur.state[1][1] == 'X' && cur.state[1][2] == 'X')
     || (cur.state[2][0] == 'X' && cur.state[2][1] == 'X' && cur.state[2][2] == 'X')
     || (cur.state[0][0] == 'X' && cur.state[1][1] == 'X' && cur.state[2][2] == 'X')
     || (cur.state[2][0] == 'X' && cur.state[1][1] == 'X' && cur.state[0][2] == 'X'))
    return W;
  
  else if((cur.state[0][0] == 'X' && cur.state[0][1] == 'X' && cur.state[0][2] == 'X')
	  || (cur.state[1][0] == 'X' && cur.state[1][1] == 'X' && cur.state[1][2] == 'X')
	  || (cur.state[2][0] == 'X' && cur.state[2][1] == 'X' && cur.state[2][2] == 'X')
	  || (cur.state[0][0] == 'X' && cur.state[1][1] == 'X' && cur.state[2][2] == 'X')
	  || (cur.state[2][0] == 'X' && cur.state[1][1] == 'X' && cur.state[0][2] == 'X'))
    return L;
  
  else if(cur.open == 0)
    return D;
  
  else
    return diff(cur);
}

Node setVal(Node cur) {
  Node next;
  next.open = cur.open;
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      next.state[i][j] = cur.state[i][j];
    }
  }
  
  return next;
}

void minimax_decision(Node cur) {
  if(terminal_test(cur))
    return;

  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(cur.state[i][j] == '_') {
	Node next = setVal(cur);
	if(pl == 1)
	  next.state[i][j] = 'O';
	else
	  next.state[i][j] = 'X';
	nei.push_back(next);
      }
    }
  }
  
  if(pl == 1) {
    
  }
  else {
    
  }
  
  nei.clear();
  cur.open--;
}

void max_value() {
  
}

void min_value() {
  
}

char xoro(int m) {
  if(m == 1)
    return 'X';
  return 'O';
}

int main() {
  printf("Player 1 or 2? ");
  scanf("%d", &pl); //player1 or player2
  if(pl != 1 && pl != 2) {
    printf("That is not a player. Try again.\n");
    return 0;
  }
  
  return 0;
}
