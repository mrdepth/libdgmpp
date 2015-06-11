#pragma once
#include <stdexcept>
#include "types.h"
#include <sqlite3.h>

//#include "ThirdParty/sqlite3.h"
//#include <boost/exception/all.hpp>


namespace eufe {

	class Compiler
	{
	public:

		//typedef boost::error_info<struct SqliteExceptionInfoTag, std::string> SqliteExceptionInfo;
		//struct SqliteException : virtual boost::exception {};
		//struct SqliteExpcetion: std::logic_error {};
		typedef std::runtime_error SqliteException;
		
		Compiler(const std::string& databasePath, const std::string& outputPath);
		~Compiler(void);
		void compile();
	private:

		typedef std::map<std::string, std::string> Row;
		typedef std::map<std::string, Row> RowsMap;
		
		typedef std::basic_string<Byte> MemoryBlock;
		typedef std::map<std::string, MemoryBlock> CompiledExpressionsMap;

		std::string databasePath_;
		std::string outputPath_;

		RowsMap expressions_;
		RowsMap operands_;
		RowsMap effects_;
		CompiledExpressionsMap compiledExpressionsMap_;

		
		
		MemoryBlock compileExpression(Row& expression);
		MemoryBlock compileEffect(Row& effect);
		
		size_t addExpression(Row& expression, CompiledExpressionsMap& expressionsMap);
		
		static Row callback(int argc, char** argv, char** azColName);
		static int callbackExpression(void* context, int argc, char** argv, char** azColName);
		static int callbackOperand(void* context, int argc, char** argv, char** azColName);
		static int callbackEffect(void* context, int argc, char** argv, char** azColName);

		std::string stringRepresentation(const MemoryBlock& memoryBlock);
	};

};
