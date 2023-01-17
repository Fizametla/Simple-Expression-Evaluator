#include "Transformer.h"

namespace ds {

/**
 * Transform the token stream from infix to postfix form.
 *
 * @param infix list of tokens in infix notation
 * @return stack<Token> token stack in postfix notation
 */
stack<Token>
InfixToPostfixTransformer::infixToPostfix(const VList<Token> &infix) {
  stack<Token> opStk; 
  stack<Token> postfixStk;

  for (int i = 0; i < infix.size(); i++) {
    Token item = infix.get(i); // the i-th token

    // if number or variable push Token directly to postfixStk
    if (item.is_one_of(Token::Kind::Variable, Token::Kind::Number)){
        postfixStk.push(item);} 
    
    // if operator (plus or minus)
    else if (item.is_one_of(Token::Kind::Plus, Token::Kind::Minus)) { 
      // transfer tokens from opStk to postfixStk while opStk not empty && token is not LeftParen
      while(opStk.size() > 0 && (opStk.top().is(Token::Kind::LeftParen))== false 
      && !(opStk.top().is(Token::Kind::Equal))) {
        Token transfer = opStk.top();
        opStk.pop();
        postfixStk.push(transfer);} 
      // push Token operator onto opStk 
      opStk.push(item);}

    // if Equal - push directly to stack 
    else if (item.is(Token::Kind::Equal)) {
      opStk.push(item);
    }

    // if LeftParen push Token directly onto opStk
    else if (item.is(Token::Kind::LeftParen))
      opStk.push(item);

    // if RightParen  
    else if (item.is(Token::Kind::RightParen)) {
      while(opStk.size() > 0){
        if (opStk.top().is(Token::Kind::LeftParen)){ // break if LeftParen 
          opStk.pop();
          break;}
        // transfer tokens from opStk to postfikStk while opStk not empty
        Token transfer = opStk.top();
        opStk.pop();
        postfixStk.push(transfer);}
    } 
    
    // if Semicolon 
    // transfer reamining token from opStk to postfixStk
    else if (item.is(Token::Kind::Semicolon)){

      while (!(opStk.empty())){
        Token transfer = opStk.top();
        postfixStk.push(transfer);
        opStk.pop();
      }
      postfixStk.push(item);
    }
  }
  // transfer remaining tokens from opStk to postfixStk

    /** while (opStk.size() > 0){
    Token transfer = opStk.top();
    opStk.pop();
    postfixStk.push(transfer);}
    */ 
  // return postfixStk 
  return postfixStk;
  
}

}// namespace ds
