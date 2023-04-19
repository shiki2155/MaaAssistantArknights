#include "MatchImageAnalyzerConfig.h"

#include "Config/TaskData.h"

void asst::MatchImageAnalyzerConfig::set_params(Params params)
{
    m_params = std::move(params);
}

void asst::MatchImageAnalyzerConfig::set_task_info(const std::shared_ptr<TaskInfo>& task_ptr)
{
    _set_task_info(*std::dynamic_pointer_cast<MatchTaskInfo>(task_ptr));
}

void asst::MatchImageAnalyzerConfig::set_task_info(const std::string& task_name)
{
    set_task_info(Task.get(task_name));
}

void asst::MatchImageAnalyzerConfig::set_templ(std::variant<std::string, cv::Mat> templ)
{
    m_params.templ = std::move(templ);
}

void asst::MatchImageAnalyzerConfig::set_threshold(double templ_thres) noexcept
{
    m_params.templ_thres = templ_thres;
}

void asst::MatchImageAnalyzerConfig::set_mask_range(int lower, int upper, bool mask_with_src, bool mask_with_close)
{
    m_params.mask_range = std::make_pair(lower, upper);
    m_params.mask_with_src = mask_with_src;
    m_params.mask_with_close = m_params.mask_with_close;
}

void asst::MatchImageAnalyzerConfig::_set_task_info(MatchTaskInfo task_info)
{
    m_params.templ = std::move(task_info.templ_name);
    m_params.templ_thres = task_info.templ_threshold;
    m_params.mask_range = std::move(task_info.mask_range);

    _set_roi(task_info.roi);
}
