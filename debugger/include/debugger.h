

class debugger {
public:
  debugger(std::string prog_name, pid_t pid)
      : m_prog_name{std::move(prog_name)}, m_pid{pid} {}
  void run();

private:
  std::string m_prog_name;
  pid_t m_pid;
  void handle_command(const std::string &line);
  void continue_execution();
  std::vector<std::string> split(const std::string &s, char delimiter);
  bool is_prefix(const std::string &s, const std::string &of) {
    if (s.size() > of.size())
      return false;
    return std::equal(s.begin(), s.end(), of.begin());
  }
};
