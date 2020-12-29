```
int32 DataManager::dm_cmd_handler(vector<string> &cmd, char *buf)
{
  std::ostringstream  out, err;
  dm_parse_command(cmd, out, err);
  std::string output;
  output = out.str() + err.str();
  int32 ret = snprintf(buf, DM_OUTPUT_LEN_MAX, "%s", output.c_str());
  dout(5) << __func__ << " returns " << ret << " cmd: " << cmd << dendl;
  return ret;
}
```
