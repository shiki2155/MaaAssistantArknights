#include "DebugTask.h"

#include <filesystem>

#include "Utils/NoWarningCV.h"

#include "Utils/ImageIo.hpp"
#include "Utils/Logger.hpp"
#include "Vision/Battle/BattlefieldMatcher.h"
#include "Vision/Battle/BattlefieldClassifier.h"
#include "Vision/Miscellaneous/DepotAnalyzer.h"
#include "Vision/Miscellaneous/StageDropsAnalyzer.h"

asst::DebugTask::DebugTask(const AsstCallback& callback, Assistant* inst) : InterfaceTask(callback, inst, TaskType) {}

bool asst::DebugTask::run()
{
    test_battle_image();

    return true;
}

void asst::DebugTask::test_drops()
{
    size_t total = 0;
    size_t success = 0;
    for (const auto& entry : std::filesystem::directory_iterator("../../test/drops/screenshots/zh_cn")) {
        cv::Mat image = asst::imread(entry.path());
        if (image.empty()) {
            continue;
        }
        total += 1;
        cv::Mat resized;
        cv::resize(image, resized, cv::Size(1280, 720), 0, 0, cv::INTER_AREA);
        StageDropsAnalyzer analyzer(resized);
        success += analyzer.analyze();
    }
    Log.info(__FUNCTION__, success, "/", total);
}

void asst::DebugTask::test_skill_ready()
{
    int total = 0;
    int correct = 0;
    for (const auto& entry : std::filesystem::directory_iterator(R"(../../test/skill_ready/y)")) {
        cv::Mat image = imread(entry.path().string());
        BattlefieldClassifier analyzer(image);
        total++;
        if (analyzer.analyze()) {
            correct++;
        }
    }
    for (const auto& entry : std::filesystem::directory_iterator(R"(../../test/skill_ready/n)")) {
        cv::Mat image = imread(entry.path().string());
        BattlefieldClassifier analyzer(image);
        total++;
        if (!analyzer.analyze()) {
            correct++;
        }
    }
    Log.info(__FUNCTION__, correct, "/", total, ",", double(correct) / total);
}

void asst::DebugTask::test_battle_image()
{
    cv::Mat image = asst::imread(utils::path("1.png"));
    cv::Mat resized;
    cv::resize(image, resized, cv::Size(1280, 720), 0, 0, cv::INTER_AREA);
    BattlefieldMatcher analyzer(resized);
    analyzer.set_object_to_analyze(BattlefieldMatcher::ObjectOfInterest::Oper);
    analyzer.analyze();
}
