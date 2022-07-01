#pragma once
#include <chrono>

template <class T>
class AnimTimer final {
public:
	AnimTimer(const std::vector<T>& table, const std::chrono::milliseconds period) :
		table_(table), period_(period) {
			if (table_.size() > 0) {
				step_ = period_ / table_.size();
			}
		}
	~AnimTimer() = default;

	void reset() {
		tableIdx_ = 0;
		lastRequest_ = std::chrono::steady_clock::now();
	};

	T getNextTableEntry() {
		auto now = std::chrono::steady_clock::now();
		auto next = lastRequest_ + step_;

		while (now > next) {
			next += step_;
			if (++tableIdx_ > table_.size() - 1) {
				tableIdx_ = 0;
				next += period_;
			}
		}
		lastRequest_ = now;
		return table_.at(tableIdx_);
	}

private:
	const std::vector<T>& table_;
	const std::chrono::milliseconds period_;
	std::chrono::milliseconds step_;
	std::chrono::steady_clock::time_point lastRequest_;
	size_t tableIdx_;
};
