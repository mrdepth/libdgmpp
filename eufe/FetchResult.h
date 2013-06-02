#pragma once
#include <string>
#include "Blob.h"

namespace eufe {
	class FetchResult {
	public:
		virtual bool next() = 0;
		virtual int getInt(int columnIndex) = 0;
		virtual double getDouble(int columnIndex) = 0;
		virtual std::string getText(int columnIndex) = 0;
		virtual Blob getBlob(int columnIndex) = 0;
		virtual void finalize() = 0;
	};
}