/*
 * File:   Expr.h
 * Author: thewaffledimension
 *
 * Generated on October 28, 2018, 5:08 PM
 */


#include <vector>;
#include <any>
#include "Token.h"

static struct Expr {
	struct Visitor;
	struct Literal;
	struct Variable;
	struct Assign;
	struct Unary;
	struct Binary;
	struct Grouping;

	template <class R>
	virtual R accept(Visitor<R> visitor) = 0;
};

template <class R>
struct Expr::Visitor {
	virtual R visitLiteralExpr(Expr::Literal expr) = 0;
	virtual R visitVariableExpr(Expr::Variable expr) = 0;
	virtual R visitAssignExpr(Expr::Assign expr) = 0;
	virtual R visitUnaryExpr(Expr::Unary expr) = 0;
	virtual R visitBinaryExpr(Expr::Binary expr) = 0;
	virtual R visitGroupingExpr(Expr::Grouping expr) = 0;
};

static struct Expr::Literal : public Expr {
	std::any value;

	Literal(std::any value) {
		this.value = value;
	}

	template <class R>
	virtual R accept(R& visitor) {
		return visitor.visitLiteralExpr(*this);
	}
};


static struct Expr::Variable : public Expr {
	Token name;

	Variable(Token name) {
		this.name = name;
	}

	template <class R>
	virtual R accept(R& visitor) {
		return visitor.visitVariableExpr(*this);
	}
};


static struct Expr::Assign : public Expr {
	Token name;
	Expr value;

	Assign(Token name, Expr value) {
		this.name = name;
		this.value = value;
	}

	template <class R>
	virtual R accept(R& visitor) {
		return visitor.visitAssignExpr(*this);
	}
};


static struct Expr::Unary : public Expr {
	Token op;
	Expr right;

	Unary(Token op, Expr right) {
		this.op = op;
		this.right = right;
	}

	template <class R>
	virtual R accept(R& visitor) {
		return visitor.visitUnaryExpr(*this);
	}
};


static struct Expr::Binary : public Expr {
	Expr left;
	Token op;
	Expr right;

	Binary(Expr left, Token op, Expr right) {
		this.left = left;
		this.op = op;
		this.right = right;
	}

	template <class R>
	virtual R accept(R& visitor) {
		return visitor.visitBinaryExpr(*this);
	}
};


static struct Expr::Grouping : public Expr {
	Expr expression;

	Grouping(Expr expression) {
		this.expression = expression;
	}

	template <class R>
	virtual R accept(R& visitor) {
		return visitor.visitGroupingExpr(*this);
	}
};


