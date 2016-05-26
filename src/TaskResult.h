#pragma once

template<class TResult>
class TaskResult
{
public:
	static TaskResult CreateWithRetryAfter(int retryAfter)
	{
		TaskResult taskResult;
		taskResult.hasContent = false;
		taskResult.retryAfter = retryAfter;
		return taskResult;
	}

	static TaskResult CreateWithResult(const TResult& result)
	{
		TaskResult taskResult;
		taskResult.hasContent = true;
		taskResult.retryAfter = 0;
		taskResult.result = result;
		return taskResult;
	}

	// move
	TaskResult(TaskResult&& orig)
	{
		hasContent = std::move(orig.hasContent);
		retryAfter = std::move(orig.retryAfter);
		result = std::move(orig.result);
	}

	TaskResult& operator=(TaskResult&& right)
	{
		hasContent = std::move(right.hasContent);
		retryAfter = std::move(right.retryAfter);
		result = std::move(right.result);
		return *this;
	}

	bool HasContent() const { return hasContent; }
	int GetRetryAfter() const { return retryAfter; }
	TResult GetResult() const { return result; }

	template<class TSourceResult, typename ConvertFunc>
	static TaskResult<TResult> ConvertResult(const TaskResult<TSourceResult>& source, ConvertFunc& convertFunc)
	{
		if (!source.HasContent())
			return TaskResult<TResult>::CreateWithRetryAfter(source.GetRetryAfter());
		return TaskResult<TResult>::CreateWithResult(convertFunc(source.GetResult()));
	}

	virtual ~TaskResult()
	{
	}

private:
	TaskResult()
	{
	}

	TaskResult(const TaskResult& orig);
	TaskResult& operator=(const TaskResult& rhs);

	bool hasContent;
	int retryAfter;
	TResult result;
};
