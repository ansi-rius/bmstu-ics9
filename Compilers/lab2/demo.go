package main

import (
	"fmt"
	"go/ast"
	"go/format"
	"go/parser"
	//"go/printer"
	"go/token"
	"os"
)

func test(a int) {
	
}

func insertNameAndVal(file *ast.File) {
	var funName string;
	var funParam string;
	ast.Inspect(file, func(node ast.Node) bool {
		if FuncDecl, ok := node.(*ast.FuncDecl); ok {
			if len(FuncDecl.Type.Params.List) == 1 {
				if a, ok:= FuncDecl.Type.Params.List[0].Type.(*ast.Ident); ok {
					if a.Name =="int" {

						funParam = FuncDecl.Type.Params.List[0].Names[0].Name;

						//правильный ли доступ к имени?
						funName = FuncDecl.Name.Name;
					
						FuncDecl.Body.List = append(
							[]ast.Stmt{
								&ast.ExprStmt{
									X: &ast.CallExpr{
										Fun: &ast.SelectorExpr{
											X:   ast.NewIdent("fmt"),
											Sel: ast.NewIdent("Printf"),
										},
										Args: []ast.Expr{
											&ast.BasicLit{
												Kind:  token.INT,
												Value: "\""+funName+"\"",
											},
										},
									},
								},
							},
							FuncDecl.Body.List...,
						)
						FuncDecl.Body.List = append(
							[]ast.Stmt{
								&ast.ExprStmt{
									X: &ast.CallExpr{
										Fun: &ast.SelectorExpr{
											X:   ast.NewIdent("fmt"),
											Sel: ast.NewIdent("Printf"),
										},
										Args: []ast.Expr{
											&ast.BasicLit{
												Kind:  token.INT,
												Value: "\"%d\","+funParam,
											},
										},
									},
								},
							},
							FuncDecl.Body.List...,
						)
					};
				};
			};
			//fmt.Printf("%s",Type.Params.List[0]);
		};
		return true
	})
}

func main() {
	if len(os.Args) != 2 {
		return
	}

	fset := token.NewFileSet()
	if file, err := parser.ParseFile(fset, os.Args[1], nil, parser.ParseComments); err == nil {
		insertNameAndVal(file)
		test(6)

		if format.Node(os.Stdout, fset, file) != nil {
			fmt.Printf("Formatter error: %v\n", err)
		}
		//ast.Fprint(os.Stdout, fset, file, nil)
	} else {
		fmt.Printf("Errors in %s\n", os.Args[1])
	}
}
