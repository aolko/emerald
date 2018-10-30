/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AstToSource.h
 * Author: thewaffledimension
 *
 * Created on October 29, 2018, 10:12 PM
 */

#ifndef ASTTOSOURCE_H
#define ASTTOSOURCE_H

#include <vector>
#include <memory>
#include <any>
#include "Expr.h"
#include "Stmt.h"

class AstToSource : public Stmt::Visitor<void>, public Expr::Visitor<std::any> {
public:
    AstToSource();
    void convert(std::vector<std::unique_ptr<Stmt>> stmts);
    
    void visitBlockStmt(Stmt::Block stmt) override;
    void visitExpressionStmt(Stmt::Expression stmt) override;
    void visitIfStmt(Stmt::If stmt) override;
    
    std::any visitAssignExpr(Expr::Assign expr) override;
    std::any visitBinaryExpr(Expr::Binary expr) override;
    std::any visitLiteralExpr(Expr::Literal expr) override;
    std::any visitUnaryExpr(Expr::Unary expr) override;
    std::any visitVariableExpr(Expr::Variable expr) override;
    std::any visitGroupingExpr(Expr::Grouping expr) override;
private:
    std::vector<std::unique_ptr<Stmt>> stmts;
    
    void execute(std::unique_ptr<Stmt> stmt);
    std::any evaluate(std::unique_ptr<Expr> expr);
};

#endif /* ASTTOSOURCE_H */

