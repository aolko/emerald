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

std::string AstToSource::convert(std::vector<std::unique_ptr<Stmt>> stmts) {
    this->stmts = std::move(stmts);
    newSrc = "";
    
    try {
        for (int i = 0; i < stmts.size(); i++) {
            std::unique_ptr<Stmt> stmt = std::move(stmts[i]);
            execute(std::move(stmt));
        }
    } catch (RuntimeError error) {
        Log::runtimeError(error);
        return "";
    }
    
    return newSrc;
}

void AstToSource::visitBlockStmt(Stmt::Block stmt) {
    blockLevel++;
    for (int i = 0; i < stmt.statements.size(); i++) {
        indentLine();
        
        execute(std::move(stmt.statements[i]));
    }
    blockLevel--;
}

void AstToSource::visitExpressionStmt(Stmt::Expression stmt) {
    indentLine();
    evaluate(std::move(stmt.expression));
}

void AstToSource::visitIfStmt(Stmt::If stmt) {
    indentLine();
    newSrc += "if ";
    evaluate(std::move(stmt.condition));
    newSrc += ":";
    if (stmt.trueBody)
        execute(std::move(stmt.trueBody));
    if (stmt.falseBody) {
        indentLine();
        newSrc += "else: ";
        execute(std::move(stmt.falseBody));
    }
}

std::any AstToSource::visitAssignExpr(Expr::Assign expr) {
    std::any value = evaluate(std::move(expr.value));
    
    return value;
}

std::any AstToSource::visitBinaryExpr(Expr::Binary expr) {
    std::unique_ptr<Expr> left = std::move(expr.left);
    std::unique_ptr<Expr> right = std::move(expr.right);
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

void AstToSource::indentLine() {
    newSrc += '\n';
    for (int j = 0; j < blockLevel; j++) {
        newSrc += '\t';
    }
}