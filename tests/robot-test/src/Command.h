#pragma once

// Generic command implementation.

namespace detail
{

template <std::size_t... Types>
struct index {};

template <std::size_t N, std::size_t... Types>
struct gen_seq : gen_seq<N - 1, N - 1, Types...> {};

template <std::size_t... Types>
struct gen_seq<0, Types...> : index<Types...> {};

}	// namespace detail

template <typename Class>
class ICommand
{
public:
	virtual ~ICommand() {}

	//
	// Public interface.
	//
public:
	//! Executes command on the specified target.
	virtual void Execute(Class& instance) const = 0;
};

template <typename Class, typename... Args>
class Command
	: public ICommand<Class>
{
	//
	// Public types.
	//
public:
	typedef void(Class::*MethodType)(Args...);

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	Command(MethodType method, Args&&... args)
		: args_(std::forward<Args>(args)...)
		, method_(method)
	{
	}

	//
	// Public interface.
	//
public:
	//! Executes command on the specified target.
	void Execute(Class& instance) const override final
	{
		ExecuteImpl(instance, args_);
	}

	//
	// Private methods.
	//
private:
	template <typename... Types, std::size_t... Is>
	void ExecuteImpl(Class& instance, const std::tuple<Types...>& tup, detail::index<Is...>) const
	{
		(instance.*method_)(std::get<Is>(tup)...);
	}

	template <typename... Types>
	void ExecuteImpl(Class& instance, const std::tuple<Types...>& tup) const
	{
		ExecuteImpl(instance, tup, detail::gen_seq<sizeof...(Types)>{});
	}

	//
	// Private data members.
	//
private:
	//! Command methods arguments.
	const std::tuple<Args...> args_;
	//! Command method to call.
	MethodType method_;
};

//! Helper function for automatic type deduction.
template <typename Class, typename Method, typename... Args>
std::shared_ptr<ICommand<Class>> MakeCommand(Method method, Args&&... args)
{
	return std::shared_ptr<ICommand<Class>>(new Command<Class, Args...>(
		std::forward<Method>(method), std::forward<Args>(args)...));
}
