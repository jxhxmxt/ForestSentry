--
-- PostgreSQL database dump
--

-- Dumped from database version 15.2
-- Dumped by pg_dump version 15.2

-- Started on 2024-06-30 20:04:15

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 3324 (class 1262 OID 33713)
-- Name: aca; Type: DATABASE; Schema: -; Owner: postgres
--

CREATE DATABASE aca WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE_PROVIDER = libc LOCALE = 'English_United States.1252';


ALTER DATABASE aca OWNER TO postgres;

\connect aca

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 4 (class 2615 OID 2200)
-- Name: public; Type: SCHEMA; Schema: -; Owner: pg_database_owner
--

CREATE SCHEMA public;


ALTER SCHEMA public OWNER TO pg_database_owner;

--
-- TOC entry 3325 (class 0 OID 0)
-- Dependencies: 4
-- Name: SCHEMA public; Type: COMMENT; Schema: -; Owner: pg_database_owner
--

COMMENT ON SCHEMA public IS 'standard public schema';


SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 214 (class 1259 OID 33714)
-- Name: records; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.records (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    latitude double precision NOT NULL,
    longitude double precision NOT NULL,
    humidity real NOT NULL,
    temperature real NOT NULL,
    smoke_level integer NOT NULL,
    rain_status boolean NOT NULL,
    alert_level integer NOT NULL,
    device_id character varying NOT NULL,
    "timestamp" timestamp without time zone DEFAULT CURRENT_TIMESTAMP
);


ALTER TABLE public.records OWNER TO postgres;

--
-- TOC entry 3318 (class 0 OID 33714)
-- Dependencies: 214
-- Data for Name: records; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.records (id, latitude, longitude, humidity, temperature, smoke_level, rain_status, alert_level, device_id, "timestamp") FROM stdin;
\.


--
-- TOC entry 3175 (class 2606 OID 33719)
-- Name: records records_pk; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.records
    ADD CONSTRAINT records_pk PRIMARY KEY (id);


-- Completed on 2024-06-30 20:04:15

--
-- PostgreSQL database dump complete
--

