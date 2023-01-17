#include "Evaluator.h"

namespace ds {

/**
 * Create an expression tree from a stack of tokens in postifx form
 *
 * @param tokenStk the postfix tokens; may contain variables, numbers, plus,
 * minus, equal, and semicolon
 * @return ExprTreeNode* the root of the generated expression tree
 */
ExprTreeNode *Evaluator::buildExprTree(std::stack<Token> &tokenStk) {
  // TODO:
  if (tokenStk.empty()){
      return nullptr;
  }

    Token item = tokenStk.top();
    tokenStk.pop();

    /** base case: Token is variable or number 
     * Single Token is added to tree and root is returned 
     * return root of tree
     */
    if (item.is_one_of(Token::Kind::Variable, Token::Kind::Number)){
      ExprTreeNode *n = new ExprTreeNode(item);
      return n;
    }

    /** Case: Equal or Semicolon or Minus or Plus 
     *Make new tree with Token as root
     *First recursively define expr2, then recursively define expr1
     *return root
     */
    else if (item.is_one_of(Token::Kind::Semicolon, Token::Kind::Equal,Token::Kind::Plus, Token::Kind::Minus)){
      ExprTreeNode *n = new ExprTreeNode(item);
      
      n -> expr2 = buildExprTree(tokenStk);
      n -> expr1 = buildExprTree(tokenStk);
      return n;
    }

    return nullptr;
}
  /**
   * Evaluate the given expression tree
   *
   * @param root the root of the expression tree
   * @param varTbl the map from a variable to its value
   * @return BigInt the result of the expression; if the tree is empty, simply
   * return an empty BigInt
   */
  BigInt Evaluator::evaluateExprTree(const ExprTreeNode *root,
                                     std::map<std::string, BigInt> &varTbl) {
    // TODO:

    // base case 
    // return empty BigInt
    if (root == nullptr) {
      return BigInt();
    }
    
    Token item = root->token; // current token 

    // Number
    // creates a BigInt of the Number and returns it  
    if (item.is(Token::Kind::Number)) {
      BigInt num(root-> token.lexeme);
      return num;
    }

    // Variable
    // Returns the value of variable 
    else if (item.is(Token::Kind::Variable)){
      return varTbl[root->token.lexeme];
    }

    //Plus
    // Finds expr 1 and expr2 
    // Adds the two subexpressions (branches)
    else if(item.is(Token::Kind::Plus)){
      return (evaluateExprTree(root->expr1, varTbl) +
              evaluateExprTree(root->expr2, varTbl));
    }

    // Minus
    // Evualuate subexpressions expr1 and expr2
    // Finds absolute difference of two subexpressions (branches)
    else if(item.is(Token::Kind::Minus)){
      return (evaluateExprTree(root->expr1, varTbl) -
              evaluateExprTree(root->expr2, varTbl));
    }

    // Equal
    // Evalute expr2
    // Save result in varTbl
    else if(item.is(Token::Kind::Equal)){
      varTbl[root->expr1->token.lexeme] = evaluateExprTree(root->expr2, varTbl);
      return varTbl[root->expr1->token.lexeme];
    }

   //Semicolon
   //Evaluate expr1
   //Evluate and return expr2
   else if(item.is(Token::Kind::Semicolon)){
      evaluateExprTree(root->expr1, varTbl);
      return (evaluateExprTree(root->expr2, varTbl));
    }

    // return an empty BigInt
    return BigInt();
  }
} // namespace ds