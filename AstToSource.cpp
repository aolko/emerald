/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AstToSource.cpp
 * Author: thewaffledimension
 * 
 * Created on October 29, 2018, 10:12 PM
 */

#include "AstToSource.h"
#include "Log.h"

AstToSource::AstToSource() {
    
}

void AstToSource::convert(std::vector<std::unique_ptr<Stmt>> stmts) {
    this->stmts = std::move(stmts);
    
    try {
        for (int i = 0; i < stmts.size(); i++) {
            std::unique_ptr<Stmt> stmt = std::move(stmts[i]);
            execute(std::move(stmt));
        }
    } catch (RuntimeError error) {
        Log::runtimeError(error);
    }
}

void AstToSource::visitBlockStmt(Stmt::Block stmt) {
    
}

void AstToSource::visitExpressionStmt(Stmt::Expression stmt) {
    
}

void AstToSource::visitIfStmt(Stmt::If stmt) {
    
}

std::any AstToSource::visitAssignExpr(Expr::Assign expr) {
    std::any value = evaluate(std::move(expr.value));
    
    return value;
}

std::any AstToSource::visitBinaryExpr(Expr::Binary expr) {
    
}

std::any AstToSource::visitLiteralExpr(Expr::Literal expr) {
    
}

std::any AstToSource::visitUnaryExpr(Expr::Unary expr) {
    
}

std::any AstToSource::visitVariableExpr(Expr::Variable expr) {
    
}

std::any AstToSource::visitGroupingExpr(Expr::Grouping expr) {
    
}

void AstToSource::execute(std::unique_ptr<Stmt> stmt) {
    Stmt* stmtPtr = stmt.get();
    stmtPtr->accept(*this);
}

std::any AstToSource::evaluate(std::unique_ptr<Expr> expr) {
    Expr* exprPtr = expr.get();
    return exprPtr->accept(*this);
}