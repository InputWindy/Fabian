#pragma once
struct INoneCopyable
{
	INoneCopyable() = default;
	virtual ~INoneCopyable() = default;

	INoneCopyable(const INoneCopyable&) = delete;
	INoneCopyable(INoneCopyable&&) = delete;

	void operator=(const INoneCopyable&) = delete;
	void operator=(INoneCopyable&&) = delete;
};
