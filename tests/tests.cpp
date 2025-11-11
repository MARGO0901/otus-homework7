#define BOOST_TEST_MODULE test_bulk
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>

bool files_are_equal(const std::string &file1, const std::string &file2) {
    std::ifstream f1(file1), f2(file2);
    if (!f1.is_open() || !f2.is_open()) {
        throw std::runtime_error("не удалось открыть файлы");
    }
    std::ostringstream ss1, ss2;
    ss1 << f1.rdbuf();
    ss2 << f2.rdbuf();

    std::string content1 = ss1.str();
    std::string content2 = ss2.str();

    std::cout << "File1 content: '" << content1 << "'" << std::endl;
    std::cout << "File2 content: '" << content2 << "'" << std::endl;
    std::cout << "Files equal: " << (content1 == content2) << std::endl;

    return content1 == content2;
}

void run_bulk_test(std::string&& test_name) {

    std::string input = test_name + ".in";
    std::string output = test_name + ".out";

    boost::filesystem::path project_root =
        boost::filesystem::current_path().parent_path();
    std::string input_file = (project_root / "tests" / input).string();
    std::string output_file = (project_root / "tests" / output).string();
    std::string bulk_exe =
        (project_root / "src" / "bulk").string();

    std::cout << "Project root: " << project_root << std::endl;
    std::cout << "Input file: " << input_file
              << " exists: " << boost::filesystem::exists(input_file)
              << std::endl;
    std::cout << "Output file: " << output_file
              << " exists: " << boost::filesystem::exists(output_file)
              << std::endl;
    std::cout << "Bulk exe: " << bulk_exe
              << " exists: " << boost::filesystem::exists(bulk_exe)
              << std::endl;

    // Проверка существования входных файлов
    BOOST_REQUIRE(boost::filesystem::exists(input_file));
    BOOST_REQUIRE(boost::filesystem::exists(output_file));
    BOOST_REQUIRE(boost::filesystem::exists(bulk_exe));

    // Создание временного файла
    boost::filesystem::path temp_dir = boost::filesystem::temp_directory_path();
    boost::filesystem::path temp_file = temp_dir / ("bulk_test_" + test_name + ".txt");

    // Удалить файл, если он уже существует
    if (boost::filesystem::exists(temp_file)) {
        boost::filesystem::remove(temp_file);
    }

    // Запуск команды
    std::string command =
        bulk_exe + " 3 < " + input_file + " > " + temp_file.string();
    std::cout << "Command: " << command << std::endl;
    int ret = std::system(command.c_str());
    BOOST_CHECK_EQUAL(ret, 0);

    // Проверка, что выходной файл создан
    bool file_exists = boost::filesystem::exists(temp_file);
    BOOST_REQUIRE(file_exists);

    // Сравнение файлов
    bool are_equal = files_are_equal(output_file, temp_file.string());
    BOOST_CHECK(are_equal);

    // Очистка
    if (boost::filesystem::exists(temp_file)) {
        boost::filesystem::remove(temp_file);
    }
}

BOOST_AUTO_TEST_SUITE(test_bulk)

BOOST_AUTO_TEST_CASE(test_basic) { BOOST_CHECK(true); }

BOOST_AUTO_TEST_CASE(test_1) { 
    run_bulk_test(std::move("test1"));
}

BOOST_AUTO_TEST_CASE(test_2) { 
    run_bulk_test(std::move("test2")); 
}

BOOST_AUTO_TEST_SUITE_END()