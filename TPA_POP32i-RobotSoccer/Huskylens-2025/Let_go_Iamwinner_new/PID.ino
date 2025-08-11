void heading(float spd, float theta, float spYaw) {
  head_error = spYaw - pvYaw;
  head_i = head_i + head_error;
  head_i = constrain(head_i, -180, 180);
  head_d = head_error - head_pError;
  head_w = (head_error * head_Kp) + (head_i * head_Ki) + (head_d * head_Kd);
  head_w = constrain(head_w, -100, 100);
  holonomic(spd, theta, head_w);
  head_pError = head_error;
}
void rotate() {
  rot_error = sp_rot - ballPosX;
  rot_d = rot_d + rot_error;
  rot_d = constrain(rot_d, -100, 100);
  rot_d = rot_error - rot_pError;
  rot_pError = rot_error;
  rot_w = (rot_error * rot_Kp) + (rot_i * rot_Ki) + (rot_d * rot_Kd);
  rot_w = constrain(rot_w, -100, 100);
}
void follow() {
  fli_error = spFli - ballPosY;
  fli_i = fli_i + fli_error;
  fli_i = constrain(fli_i, -100, 100);
  fli_d = fli_error - fli_pError;
  fli_pError = fli_error;
  fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd;
  fli_spd = constrain(fli_spd, -100, 100);
}