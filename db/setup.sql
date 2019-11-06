CREATE UNLOGGED payload (
  data JSONB
);

CREATE UNLOGGED TABLE tmp (
  data JSONB
);

CREATE TABLE ddex (
  id VARCHAR(32) PRIMARY KEY,
  message_version VARCHAR(5) NOT NULL,
  message_type VARCHAR(32) NOT NULL,
  message_id VARCHAR(32) NOT NULL,
  data JSONB,
  created_at TIMESTAMP NOT NULL DEFAULT NOW()
);

-- if the index searches a few predetermined attributes, 
-- BTREE is the best choice, however if the index searches arbitrary attributes 
-- prefers GIN index. In the case of using GIN index, use jsonb_path_ops 
-- as a class checking whether it simply has a key-value, but in order 
-- to check not only it has a key-value also existence of the key, 
-- better to use jsonb_ops.
CREATE INDEX idx_btree_ddex_message ON ddex USING BTREE (message_type, message_id);
CREATE INDEX idx_gin_ddex_data ON ddex USING GIN (data jsonb_ops);

CREATE OR REPLACE FUNCTION insert_trigger()
RETURNS TRIGGER language plpgsql AS $$
DECLARE
  data jsonb := new.data::jsonb->'Data';
BEGIN

    EXECUTE format('INSERT INTO ddex(id,message_version,message_type,message_id,data) VALUES($1,$2,$3,$4,$5) ON CONFLICT DO NOTHING;')
    USING MD5(new.data::text),
          new.data->>'MessageVersion',
          new.data->>'MessageType',
          new.data->>'MessageId',
          data;

    return old;
END $$;

CREATE TRIGGER insert_trigger
AFTER INSERT ON tmp
FOR EACH ROW EXECUTE PROCEDURE insert_trigger();
