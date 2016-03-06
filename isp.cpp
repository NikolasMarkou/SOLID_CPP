/* 
 * The interface-segregation principle (ISP) 
 * states that no client should be forced to depend on methods it does not use.
 * ISP splits interfaces which are very large into smaller and more specific ones so that clients
 * will only have to know about the methods that are of interest to them. 
 * Such shrunken interfaces are also called role interfaces. 
 * ISP is intended to keep a system decoupled and thus easier to refactor, change, and redeploy.
 */

#include <vector>
struct Document;

//struct IMachine
//{
//  virtual void print(std::vector<Document*> docs) = 0;
//  virtual void scan(std::vector<Document*> docs) = 0;
//  virtual void fax(std::vector<Document*> docs) = 0;
//};
//
//struct MFP : IMachine
//{
//  void print(std::vector<Document*> docs) override;
//  void scan(std::vector<Document*> docs) override;
//  void fax(std::vector<Document*> docs) override;
//};

struct IPrinter
{
  virtual void print(std::vector<Document*> docs) = 0;
};

struct IScanner
{
  virtual void scan(std::vector<Document*> docs) = 0;
};

struct Printer : IPrinter
{
  void print(std::vector<Document*> docs) override;
};

struct Scanner : IScanner
{
  void scan(std::vector<Document*> docs) override;
};

struct IMachine : IPrinter, IScanner {};

struct Machine : IMachine
{
  IPrinter& printer;
  IScanner& scanner;


  Machine(IPrinter& printer, IScanner& scanner)
    : printer{printer},
      scanner{scanner}
  {
  }

  void print(std::vector<Document*> docs) override {
    printer.print(docs);
  }
  void scan(std::vector<Document*> docs) override {
    scanner.scan(docs);
  }
};
