//
//  Rate.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 23.11.2017.
//

#pragma once

namespace dgmpp {
	template<typename Rep, typename Period = std::chrono::seconds>
	class rate {
	public:
		using rep = Rep;
		using period = Period;
		
		rate() {};
		constexpr explicit rate(const Rep& value) : rep_(value) {}
		
		template<typename Period2>
		constexpr operator rate<Rep, Period2> () noexcept {
			using r = std::ratio_divide<typename Period::period::ratio, typename Period2::period::ratio>;
			return rate<Rep, Period2>{rep_ * r::den / r::num};
		};
		
		Rep count() const noexcept {return rep_;}
		
		auto operator+ (const rate<Rep, Period>& other) const noexcept {
			return rate<Rep, Period>(rep_ + other.rep_);
		}
		
		auto operator- (const rate<Rep, Period>& other) const noexcept {
			return rate<Rep, Period>(rep_ + other.rep_);
		}
		
//		auto operator* (const rate<Rep, Period>& other) const {
//			return rate<Rep, Period>(rep_ * other.rep_);
//		}
		
		template<typename Period2, typename Rep2>
		Rep operator* (const std::chrono::duration<Rep2, Period2>& p) const noexcept {
			return rep_ * std::chrono::duration_cast<Period>(p).count();
		}
		
		auto operator/ (const rate<Rep, Period>& other) const noexcept {
			return rep_ / other.rep_;
//			return rate<Rep, Period>(rep_ / other.rep_);
		}

		template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
		auto operator* (T value) const noexcept {
			return rate<Rep, Period>(rep_ * value);
		}

		template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
		auto operator/ (T value) const noexcept {
			return rate<Rep, Period>(rep_ / value);
		}

		rate<Rep, Period>& operator+= (const rate<Rep, Period>& other) noexcept {
			rep_ += other.rep_;
			return *this;
		}
		
		rate<Rep, Period>& operator-= (const rate<Rep, Period>& other) noexcept {
			rep_ -= other.rep_;
			return *this;
		}
		
//		rate<Rep, Period>& operator*= (const rate<Rep, Period>& other) {
//			rep_ *= other.rep_;
//			return *this;
//		}
		
//		rate<Rep, Period>& operator/= (const rate<Rep, Period>& other) {
//			rep_ /= other.rep_;
//			return *this;
//		}
		
		bool operator> (const rate<Rep, Period>& other) const noexcept {
			return count() > other.count();
		}

		bool operator< (const rate<Rep, Period>& other) const noexcept {
			return count() < other.count();
		}

		bool operator>= (const rate<Rep, Period>& other) const noexcept {
			return count() >= other.count();
		}

		bool operator<= (const rate<Rep, Period>& other) const noexcept {
			return count() <= other.count();
		}
		
		bool operator== (const rate<Rep, Period>& other) const noexcept {
			return count() == other.count();
		}
		
		bool operator!= (const rate<Rep, Period>& other) const noexcept {
			return count() != other.count();
		}

		
	private:
		Rep rep_ = 0;
	};
	
	template<typename Rep, typename Period>
	auto make_rate(const Rep& value, const Period& period) noexcept {
		auto c = period.count();
		return rate<Rep, Period> (c > 0 ? value / c : Rep(0));
	}
}
