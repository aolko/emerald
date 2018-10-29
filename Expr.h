/*
 * File:   Expr.h
 * Author: thewaffledimension
 *
 * Generated on October 28, 2018, 5:08 PM
 */


#ifndef EXPR_H
#define EXPR_H

#include <memory>
#include <vector>
#include <any>
#include "Token.h"

struct Expr {
        virtual ~Expr() = default;
    
	template <class R>
	struct Visitor;
	struct Literal;
	struct Variable;
	struct Assign;
	struct Unary;
	struct Binary;
	struct Grouping;

	template <class R>
	R accept(Visitor<R> visitor) {};
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

struct Expr::Literal : public Expr {
	std::any value;

	Literal(std::any value) {
		this->value = value;
	}

	template <class R>
	R accept(R& visitor) {
		return visitor.visitLiteralExpr(*this);
	}
};


struct Expr::Variable : public Expr {
	Token name;

	Variable(Token name) {
		this->name = name;
	}

	template <class R>
	R accept(R& visitor) {
		return visitor.visitVariableExpr(*this);
	}
};


struct Expr::Assign : public Expr {
	Token name;
	std::unique_ptr<Expr> value;

	Assign(Token name, std::unique_ptr<Expr> value) {
		this->name = name;
		this->value = std::move(value);
	}

	template <class R>
	R accept(R& visitor) {
		return visitor.visitAssignExpr(*this);
	}
};


struct Expr::Unary : public Expr {
	Token op;
	std::unique_ptr<Expr> right;

	Unary(Token op, std::unique_ptr<Expr> right) {
		this->op = op;
		this->right = std::move(right);
	}

	template <class R>
	R accept(R& visitor) {
		return visitor.visitUnaryExpr(*this);
	}
};


struct Expr::Binary : public Expr {
	std::unique_ptr<Expr> left;
	Token op;
	std::unique_ptr<Expr> right;

	Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right) {
		this->left = std::move(left);
		this->op = op;
		this->right = std::move(right);
	}

	template <class R>
	R accept(R& visitor) {
		return visitor.visitBinaryExpr(*this);
	}
};


struct Expr::Grouping : public Expr {
	std::unique_ptr<Expr> expression;

	Grouping(std::unique_ptr<Expr> expression) {
		this->expression = std::move(expression);
	}

	template <class R>
	R accept(R& visitor) {
		return visitor.visitGroupingExpr(*this);
	}
};



#endif /* EXPR_H */