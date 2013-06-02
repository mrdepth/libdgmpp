#include "SqliteFetchResult.h"

using namespace eufe;

SqliteFetchResult::SqliteFetchResult(sqlite3_stmt* stmt): stmt_(stmt)
{
}

SqliteFetchResult::~SqliteFetchResult(void)
{
	finalize();
}

		
bool SqliteFetchResult::next()
{
	return stmt_ && sqlite3_step(stmt_) == SQLITE_ROW;
}

int SqliteFetchResult::getInt(int columnIndex)
{
	return sqlite3_column_int(stmt_, columnIndex);
}

double SqliteFetchResult::getDouble(int columnIndex)
{
	return sqlite3_column_double(stmt_, columnIndex);
}

std::string SqliteFetchResult::getText(int columnIndex)
{
	return reinterpret_cast<const char*>(sqlite3_column_text(stmt_, columnIndex));
}

Blob SqliteFetchResult::getBlob(int columnIndex)
{
	size_t size = sqlite3_column_bytes(stmt_, columnIndex);
	const void* blob = sqlite3_column_blob(stmt_, columnIndex);
	return Blob(blob, size);
}

void SqliteFetchResult::finalize()
{
	if (stmt_) {
		sqlite3_finalize(stmt_);
		stmt_ = NULL;
	}
}