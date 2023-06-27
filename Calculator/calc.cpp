#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "calc.hpp"


std::vector<Calc::Token> Calc::infixToPostfix(const std::vector<Token>& input) {
  //Initialize two vectors to store the output and the operators to add in during the code
  std::vector<Token> outputq;
  std::vector<Token> operatorq;
  for(Token t: input){
    //If the token is a number push it onto the output
    if(t.type=='n'){
      outputq.push_back(t);
      //std::cout << "pushing to outputq: "<< t.val << "\n";
    }
    //If the token is an open bracket push it onto the operatorq
    else if(t.type == '('){
      operatorq.push_back(t);
      //std::cout << "pushing to operatorq: "<< t.type << "\n";
    }
    //Once the code hits a closed bracket the code will move all operators off the queue
    //until it hits am open bracket
    else if(t.type == ')'){
      //std::cout << "initiating right bracket\n";
      while(!operatorq.empty()){
        if(operatorq.back().type == '('){
          operatorq.pop_back();
         // std::cout << "removing (\n";
          break;
        }
        else{
          outputq.push_back(operatorq.back());
          //std::cout << "pushing to outputq: "<< operatorq.back().type << "\n";
          operatorq.pop_back();
        }
      }
    }
    else{
      while(!operatorq.empty() && (operatorq.back().type != '(')){
        if(precedence(operatorq.back().type, t.type)){
            outputq.push_back(operatorq.back());
            //std::cout << "pushing to outputq: "<< operatorq.back().type << "\n";
            operatorq.pop_back();
        } 
        else{
          break;
        }      
      }
     operatorq.push_back(t);
     //std::cout << "pushing to operatorq: "<< t.type << "\n";
    }
  }
  //std::cout << "pushing operatorq into outputq: \n";
  while(!operatorq.empty()){   
      outputq.push_back(operatorq.back());
      //std::cout << "pushing to outputq: "<< operatorq.back().type << "\n";
      operatorq.pop_back(); 
  }
  /*for(Token t:outputq){
    if(t.type == 'n'){
      std::cout << t.val<< " ";
    }
    else{
      std::cout << t.type << " ";
    }
    
  }*/
  return outputq;
}

bool Calc::precedence(char operatorq , char inputq){
  if(operatorq == '*' || operatorq == '/'){
    return true;
  }
  else if(inputq == '*' || inputq == '/'){
    return false;
  }
  else{
    return true;
  }
}




int Calc::evalPostfix(const std::vector<Token>& tokens) {
  if (tokens.empty()) {
    return 0;
  }
  std::vector<int> stack;
  for (Token t : tokens) {
    if (t.type == 'n') {
      stack.push_back(t.val);
    } else {
      int val = 0;
      if (t.type == '+') {
        val = stack.back() + *(stack.end()-2);
      } else if (t.type == '*') {
        val = stack.back() * *(stack.end()-2);
      } else if (t.type == '-') {
        val = *(stack.end()-2) - stack.back();
      } else if (t.type == '/') {
        if (stack.back() == 0) {
          throw std::runtime_error("divide by zero");
        }
        val = *(stack.end()-2) / stack.back();
      } else {
          std::cout << "invalid token\n";
      }
      stack.pop_back();
      stack.pop_back();
      stack.push_back(val);
    }
  }
  return stack.back();
}

std::vector<Calc::Token> Calc::tokenise(const std::string& expression) {
  const std::vector<char> symbols = {'+', '-', '*', '/', '(', ')'};
  std::vector<Token> tokens {};
  for (std::size_t i =0; i < expression.size(); ++i) {
    const char c = expression[i];
    // check if c is one of '+', '-', '*', '/', '(', ')'
    if (std::find(symbols.begin(), symbols.end(), c) != symbols.end()) {
      tokens.push_back({c});
    } else if (isdigit(c)) {
      // process multiple digit integers
      std::string num {c};
      while (i + 1 < expression.size() && isdigit(expression[i + 1])) {
        ++i;
        num.push_back(expression[i]);
      }
      tokens.push_back({'n', std::stoi(num)});
    }
  }
  return tokens;
}

int Calc::eval(const std::string& expression) {
  std::vector<Token> tokens = tokenise(expression);
  std::vector<Token> postfix = infixToPostfix(tokens);
  return evalPostfix(postfix);
}
