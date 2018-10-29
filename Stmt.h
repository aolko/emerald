/*
 * File:   Expr.h
 * Author: thewaffledimension
 *
 * Generated on October 28, 2018, 5:08 PM
 */


#include <vector>;
#include <any>
#include "Token.h"

static struct Stmt {
	struct Visitor;
	struct Block;
	struct Var;
	struct If;
	struct Expression;

	template <class R>
	virtual R accept(Visitor<R> visitor) = 0;
};

template <class R>
struct Stmt::Visitor {
	virtual R visitBlockStmt(Stmt::Block stmt) = 0;
	virtual R visitVarStmt(Stmt::Var stmt) = 0;
	virtual R visitIfStmt(Stmt::If stmt) = 0;
	virtual R visitExpressionStmt(Stmt::Expression stmt) = 0;
};

static struct Stmt::Block : public Stmt {
	List<Stmt> statements;

	Block(List<Stmt> statements) {
		this.statements = statements;
	}

	template <class R>
	virtual R accept(R& visitor) {
		return visitor.visitBlockStmt(*this);
	}
};


static struct Stmt::Var : public Stmt {
	Token identifier;
	Expr value;
	bool global;

	Var(Token identifier, Expr value, bool global) {
		this.identifier = identifier;
		this.value = value;
		this.global = global;
	}

	template <class R>
	virtual R accept(R& visitor) {
		return visitor.visitVarStmt(*this);
	}
};


static struct Stmt::If : public Stmt {
	Expr condition;
	Stmt trueBody;
	Stmt falseBody;

	If(Expr condition, Stmt trueBody, Stmt falseBody) {
		this.condition = condition;
		this.trueBody = trueBody;
		this.falseBody = falseBody;
	}

	template <class R>
	virtual R accept(R& visitor) {
		return visitor.visitIfStmt(*this);
	}
};


static struct Stmt::Expression : public Stmt {
	Expr expression;

	Expression(Expr expression) {
		this.expression = expression;
	}

	template <class R>
	virtual R accept(R& visitor) {
		return visitor.visitExpressionStmt(*this);
	}
};


