/*
 * File:   Expr.h
 * Author: thewaffledimension
 *
 * Generated on October 28, 2018, 5:08 PM
 */


#ifndef STMT_H
#define STMT_H

#include <memory>
#include <vector>
#include <any>
#include "Token.h"
#include "Expr.h"

struct Stmt {
        virtual ~Stmt() = default;
    
	template <class R>
	struct Visitor;
	struct Block;
	struct Var;
	struct If;
	struct Expression;

	template <class R>
	R accept(Visitor<R> visitor) {};
};

template <class R>
struct Stmt::Visitor {
	virtual R visitBlockStmt(Stmt::Block stmt) = 0;
	virtual R visitVarStmt(Stmt::Var stmt) = 0;
	virtual R visitIfStmt(Stmt::If stmt) = 0;
	virtual R visitExpressionStmt(Stmt::Expression stmt) = 0;
};

struct Stmt::Block : public Stmt {
	std::vector<std::unique_ptr<Stmt>> statements;

	Block(std::vector<std::unique_ptr<Stmt>> statements) {
		this->statements = std::move(statements);
	}

	template <class R>
	R accept(R& visitor) {
		return visitor.visitBlockStmt(*this);
	}
};


struct Stmt::Var : public Stmt {
	Token identifier;
	std::unique_ptr<Expr> value;
	bool global;

	Var(Token identifier, std::unique_ptr<Expr> value, bool global) {
		this->identifier = identifier;
		this->value = std::move(value);
		this->global = global;
	}

	template <class R>
	R accept(R& visitor) {
		return visitor.visitVarStmt(*this);
	}
};


struct Stmt::If : public Stmt {
	std::unique_ptr<Expr> condition;
	std::unique_ptr<Stmt> trueBody;
	std::unique_ptr<Stmt> falseBody;

	If(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> trueBody, std::unique_ptr<Stmt> falseBody) {
		this->condition = std::move(condition);
		this->trueBody = std::move(trueBody);
		this->falseBody = std::move(falseBody);
	}

	template <class R>
	R accept(R& visitor) {
		return visitor.visitIfStmt(*this);
	}
};


struct Stmt::Expression : public Stmt {
	std::unique_ptr<Expr> expression;

	Expression(std::unique_ptr<Expr> expression) {
		this->expression = std::move(expression);
	}

	template <class R>
	R accept(R& visitor) {
		return visitor.visitExpressionStmt(*this);
	}
};



#endif /* STMT_H */