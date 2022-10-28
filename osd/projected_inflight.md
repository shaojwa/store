/*
  * keep tabs on object modifications that are in flight.
  * we need to know the projected existence, size, snapset,
  * etc., because we don't send writes down to disk until after
  * replicas ack.
  */
